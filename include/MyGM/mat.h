//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "vec.h"

#include "Interfaces/IArray/IArrayAdd.h"
#include "Interfaces/IMatrix/IMatrixInOut.h"
#include "Interfaces/IMatrix/IMatrixMul.h"
#include "Interfaces/IRing.h"

namespace My {
template <typename T, size_t N>
struct mat;

template <typename T_, size_t N_>
struct ImplTraits<mat<T_, N_>> {
  using IList = TemplateList<IMatrixInOut, IMatrixMul, IArrayLinear, IRing>;
  using T = vec<T_, N_>;
  static constexpr size_t N = N_;
  using F = T_;
};

template <typename T, size_t N>
struct mat : SI<mat<T, N>> {
  using SI<mat<T, N>>::SI;
};

template <size_t N>
using matf = mat<float, N>;

using matf3 = matf<3>;
using matf4 = matf<4>;

// maybe error in editor, but no compile error
static_assert(sizeof(matf4) == 16 * sizeof(float));
}  // namespace My
