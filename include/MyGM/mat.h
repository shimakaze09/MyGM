//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "vec.h"

#include "Interfaces/IMatrix/IMatrixInOut.h"
#include "Interfaces/IMatrix/IMatrixMul.h"
#include "Interfaces/IRing.h"

namespace My {
template <typename T, size_t N>
struct mat
    : SIIT_CRTP<TemplateList<IMatrixMul, IMatrixInOut, IRing, IEuclideanV>,
                mat<T, N>, TypeList<TypeList<vec<T, N>, Size<N>>, T>> {
  using SIIT_CRTP<TemplateList<IMatrixMul, IMatrixInOut, IRing, IEuclideanV>,
                  mat<T, N>,
                  TypeList<TypeList<vec<T, N>, Size<N>>, T>>::SIIT_CRTP;
};

template <size_t N>
using matf = mat<float, N>;

using matf3 = matf<3>;
using matf4 = matf<4>;

// maybe error in editor, but no compile error
static_assert(sizeof(matf4) == 16 * sizeof(float));
}  // namespace My
