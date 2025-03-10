//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "euler.h"
#include "normal.h"
#include "point.h"
#include "quat.h"
#include "rgb.h"
#include "rgba.h"
#include "vec.h"

#include <MyTemplate/SI.h>

namespace My {
template <typename T, size_t N>
struct ImplTraits<val<T, N>>
    : Array1DTraits<T, N>,
      SIMDTraits<false>,  // float4 not use SIMD
      IListTraits<IArrayLinear, IArrayHadamardProduct, IArray1D_Util> {};

template <typename T, size_t N>
struct val : SI<val<T, N>> {
  using SI<val<T, N>>::SI;

  inline val(const vec<T, N>& v) noexcept;
  inline val(const normal<T>& v) noexcept;
  inline val(const point<T, N>& v) noexcept;
  inline val(const rgb<T>& v) noexcept;
  inline val(const rgba<T>& v) noexcept;
  inline val(const quat<T>& v) noexcept;
  inline val(const euler<T>& v) noexcept;
};

template <size_t N>
using valf = val<float, N>;

using valf1 = valf<1>;
using valf2 = valf<2>;
using valf3 = valf<3>;
using valf4 = valf<4>;

template <size_t N>
using vali = val<int, N>;

using vali1 = vali<1>;
using vali2 = vali<2>;
using vali3 = vali<3>;
using vali4 = vali<4>;

template <size_t N>
using valu = val<unsigned, N>;

using valu1 = valu<1>;
using valu2 = valu<2>;
using valu3 = valu<3>;
using valu4 = valu<4>;

// maybe error in editor, but no compile error
static_assert(sizeof(valf4) == 4 * sizeof(float));
}  // namespace My

#include "detail/val.inl"
