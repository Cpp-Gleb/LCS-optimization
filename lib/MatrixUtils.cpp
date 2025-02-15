#include "MatrixUtils.h"
#include <algorithm>

Matrix CreateIdentity(int dim) {
    Matrix I(dim, std::vector<int>(dim, kInf));
    for (int i = 0; i < dim; ++i) {
        I[i][i] = 0;
    }
    return I;
}

Matrix DistanceMultiply(const Matrix &A, const Matrix &B) {
    int dim = A.size();
    Matrix C(dim, std::vector<int>(dim, kInf));
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int best = kInf;
            for (int k = 0; k < dim; k++) {
                best = std::min(best, A[i][k] + B[k][j]);
            }
            C[i][j] = best;
        }
    }
    return C;
}

static void UnitMethod(int i, int j_low, int j_high, int k_low, int k_high, const Matrix &A, const Matrix &B, std::vector<int> &ans) {
    if(j_low > j_high) return;
    int mid = (j_low + j_high) / 2;
    int best = k_low;
    int bestVal = kInf;
    for (int k = k_low; k <= k_high; k++) {
        int cost = A[i][k] + B[k][mid];
        if(cost < bestVal) {
            bestVal = cost;
            best = k;
        }
    }
    ans[mid] = best;
    UnitMethod(i, j_low, mid - 1, k_low, best, A, B, ans);
    UnitMethod(i, mid + 1, j_high, best, k_high, A, B, ans);
}

Matrix DistanceMultiplyFast(const Matrix &A, const Matrix &B) {
    int dim = A.size();
    Matrix C(dim, std::vector<int>(dim, kInf));
    for (int i = 0; i < dim; i++) {
        std::vector<int> bestIdx(dim, 0);
        UnitMethod(i, 0, dim - 1, 0, dim - 1, A, B, bestIdx);
        bool fallback = false;
        for (int j = 0; j < dim; j++) {
            int val = A[i][bestIdx[j]] + B[bestIdx[j]][j];
            if(val >= kInf) {
                fallback = true;
                break;
            }
            C[i][j] = val;
        }
        if(fallback) {
            for (int j = 0; j < dim; j++) {
                int best = kInf;
                for (int k = 0; k < dim; k++) {
                    best = std::min(best, A[i][k] + B[k][j]);
                }
                C[i][j] = best;
            }
        }
    }
    return C;
}