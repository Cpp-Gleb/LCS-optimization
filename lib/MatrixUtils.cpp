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
