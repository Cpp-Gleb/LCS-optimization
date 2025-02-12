#include "gtest/gtest.h"
#include "LCSQuery.h"
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
