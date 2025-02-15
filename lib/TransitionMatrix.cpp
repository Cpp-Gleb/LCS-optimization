#include "TransitionMatrix.h"

Matrix CreateTransitionMatrix(char c, const std::string &targetString) {
    int m = targetString.size();
    int dim = m + 1;
    Matrix trans(dim, std::vector<int>(dim, kInf));
    for (int k = 0; k < dim; k++) {
        for (int j = k; j < dim; j++) {
            if (j == k) {
                trans[k][j] = 1; // вертикальный переход
            } else if (j == k + 1) {
                if (k < m && c == targetString[k]) {
                    trans[k][j] = 0; // диагональный переход при совпадении
                } else {
                    trans[k][j] = 2; // диагональный переход при несовпадении
                }
            } else {
                if (k < m && c == targetString[k]) {
                    trans[k][j] = (j - k - 1);
                } else {
                    trans[k][j] = (j - k - 1) + 2;
                }
            }
        }
    }
    return trans;
}
