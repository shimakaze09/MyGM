//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "Interfaces/IMatrix/IMatrix.h"
#include "Interfaces/IMatrix/IMatrixInOut.h"
#include "Interfaces/IMatrix/IMatrixMul.h"
#include "Interfaces/IRing.h"
#include "vec.h"

namespace My {
template <typename T, size_t N>
struct mat
    : SIIT_CRTP<TemplateList<IMatrixInOut, IRing, IEuclideanV, IMatrixMul>,
                mat<T, N>, TypeList<TypeList<vec<T, N>, Size<N>>, T>> {
  mat() = default;
};

template <size_t N>
using matf = mat<float, N>;

using matf3 = matf<3>;
using matf4 = matf<4>;
}  // namespace My
