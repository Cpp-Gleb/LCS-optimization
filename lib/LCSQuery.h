#pragma once

#include <string>
#include <vector>
#include "MatrixUtils.h"

class LCSQuery {
public:
    LCSQuery(const std::string &source, const std::string &target);
    long long Query(int prefixSourceLength, int prefixTargetLength) const;
private:
    std::vector<Matrix> m_prefixMatrices;
    std::vector<std::vector<long long>> m_Q;
    int m_sourceLength;
    int m_targetLength;
    int m_dim;
};
