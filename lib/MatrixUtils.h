#pragma once

#include <vector>
#include <climits>

constexpr int kInf = INT_MAX / 2;
using Matrix = std::vector<std::vector<int>>;

Matrix CreateIdentity(int dim);
Matrix DistanceMultiply(const Matrix &A, const Matrix &B);
Matrix DistanceMultiplyFast(const Matrix &A, const Matrix &B);

