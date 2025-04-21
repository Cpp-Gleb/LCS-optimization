#include "gtest/gtest.h"
#include "LCSQuery.h"
#include "TransitionMatrix.h"
#include <string>
#include <chrono>

TEST(LCSQueryTest, EmptyStrings) {
    std::string s = "";
    std::string t = "";
    LCSQuery lcsQuery(s, t);
    EXPECT_EQ(lcsQuery.Query(0, 0), 0);
}

TEST(LCSQueryTest, OneEmptyString) {
    std::string s = "";
    std::string t = "abc";
    LCSQuery lcsQuery1(s, t);
    EXPECT_EQ(lcsQuery1.Query(0, 3), 0);

    s = "abc";
    t = "";
    LCSQuery lcsQuery2(s, t);
    EXPECT_EQ(lcsQuery2.Query(3, 0), 0);
}

TEST(LCSQueryTest, SingleCharacterEqual) {
    std::string s = "a";
    std::string t = "a";
    LCSQuery lcsQuery(s, t);
    EXPECT_EQ(lcsQuery.Query(1, 1), 1);
}

TEST(LCSQueryTest, SingleCharacterNotEqual) {
    std::string s = "a";
    std::string t = "b";
    LCSQuery lcsQuery(s, t);
    EXPECT_EQ(lcsQuery.Query(1, 1), 0);
}

TEST(LCSQueryTest, SymmetricStrings) {
    std::string s = "abc";
    std::string t = "abc";
    LCSQuery lcsQuery(s, t);
    EXPECT_EQ(lcsQuery.Query(3, 3), 3);
    EXPECT_EQ(lcsQuery.Query(2, 2), 2);
    EXPECT_EQ(lcsQuery.Query(1, 2), 1);
}

TEST(LCSQueryTest, DifferentStrings) {
    std::string s = "abcdef";
    std::string t = "ace";
    LCSQuery lcsQuery(s, t);
    EXPECT_EQ(lcsQuery.Query(6, 3), 3);
}

TEST(LCSQueryTest, RepeatedCharacters) {
    std::string s(100, 'a');
    std::string t(100, 'a');
    LCSQuery lcsQuery(s, t);
    EXPECT_EQ(lcsQuery.Query(100, 100), 100);
}

TEST(LCSQueryTest, PartialPrefixes) {
    std::string s = "abracadabra";
    std::string t = "avada kedavra";
    LCSQuery lcsQuery(s, t);
    EXPECT_GE(lcsQuery.Query(11, 13), 0);
    EXPECT_GE(lcsQuery.Query(7, 8), 0);
}

TEST(LCSPreprocessingPerformanceTest, PrintPreprocessingTime) {
    std::string s = "abcdefghij";
    std::string t = "abcdefghij";
    int m_dim = t.size() + 1;

    Matrix I = CreateIdentity(m_dim);

    auto start = std::chrono::high_resolution_clock::now();
    Matrix current = I;
    for (size_t i = 0; i < s.size(); i++) {
        Matrix trans = CreateTransitionMatrix(s[i], t);
        current = DistanceMultiplyFast(current, trans);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double avg_time = static_cast<double>(duration_ns) / s.size();
    std::cout << std::endl << "Preprocessing for s of length " << s.size() << " took "
              << duration_ns << " ns, average per symbol: "
              << avg_time << " ns" << std::endl << std::endl;
    SUCCEED();
}

TEST(LCSQueryPerformanceTest, SingleQueryTime) {
    std::string s = "abcdefghij";
    std::string t = "abcdefghij";
    LCSQuery lcsQuery(s, t);

    auto start = std::chrono::high_resolution_clock::now();
    int res = lcsQuery.Query(10, 10);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    EXPECT_LT(duration_ns, 1000) << "Single Query() call took too long: " << duration_ns << " ns";
}

TEST(LCSQueryPerformanceTest, MultipleQueryTime) {
    std::string s = "abcdefghij";
    std::string t = "abcdefghij";
    LCSQuery lcsQuery(s, t);
    const int iterations = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    volatile int res = 0;
    for (int i = 0; i < iterations; i++) {
        res += lcsQuery.Query(10, 10);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    EXPECT_LT(duration_ns, iterations) << "Multiple Query() calls took too long: " << duration_ns << " ns for " << iterations << " iterations";
}

TEST(LCSQueryPerformanceTest, PrintSingleQueryTime) {
    std::string s = "abcdefghij";
    std::string t = "abcdefghij";
    LCSQuery lcsQuery(s, t);

    auto start = std::chrono::high_resolution_clock::now();
    int res = lcsQuery.Query(10, 10);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Single Query() call took " << duration_ns << " ns" << std::endl << std::endl;
    SUCCEED();
}

TEST(LCSQueryPerformanceTest, PrintMultipleQueryTime) {
    std::string s = "abcdefghij";
    std::string t = "abcdefghij";
    LCSQuery lcsQuery(s, t);
    const int iterations = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    volatile int res = 0;
    for (int i = 0; i < iterations; i++) {
        res += lcsQuery.Query(10, 10);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Multiple Query() calls (" << iterations << " iterations) took "
              << duration_ns << " ns, average "
              << static_cast<double>(duration_ns) / iterations << " ns per call" << std::endl << std::endl;
    SUCCEED();
}