#include "LCSQuery.h"
#include "TransitionMatrix.h"
#include "MatrixUtils.h"
#include <algorithm>

LCSQuery::LCSQuery(const std::string &source, const std::string &target) {
    m_sourceLength = source.size();
    m_targetLength = target.size();
    m_dim = m_targetLength + 1;
    m_prefixMatrices.resize(m_sourceLength + 1);
    m_prefixMatrices[0] = CreateIdentity(m_dim);
    for (int i = 1; i <= m_sourceLength; i++) {
        Matrix trans = CreateTransitionMatrix(source[i-1], target);
        m_prefixMatrices[i] = DistanceMultiplyFast(m_prefixMatrices[i-1], trans);
    }
    m_Q.resize(m_sourceLength + 1, std::vector<long long>(m_dim, kInf));
    for (int j = 0; j < m_dim; j++) {
        m_Q[0][j] = j;
    }
    for (int i = 1; i <= m_sourceLength; i++) {
        for (int j = 0; j < m_dim; j++) {
            long long best = kInf;
            for (int k = 0; k < m_dim; k++) {
                best = std::min(best, static_cast<long long>(k) + m_prefixMatrices[i][k][j]);
            }
            m_Q[i][j] = best;
        }
    }
    for (int i = 0; i <= m_sourceLength; i++) {
        m_Q[i][0] = i;
    }
}

long long LCSQuery::Query(int p, int q) const {
    if (p <= 0 || q <= 0) return 0;
    if (p > m_sourceLength || q > m_targetLength) return -1;
    long long Fpq = m_Q[p][q];
    long long lcs = (p + q - Fpq) / 2;
    return lcs;
}
