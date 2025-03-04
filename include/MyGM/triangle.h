//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "point.h"
#include "val.h"

namespace My {
template <typename T, size_t N>
struct triangle : SI<TemplateList<IArrayInOut>, triangle<T, N>,
                     TypeList<point<T, N>, Size<3>>, T> {
  using SI<TemplateList<IArrayInOut>, triangle<T, N>,
           TypeList<point<T, N>, Size<3>>, T>::SI;

  inline T area() const noexcept;

  template <typename Container>
  inline const point<T, N> lerp(const Container& wuv) const noexcept;
};

template <size_t N>
using trianglef = triangle<float, N>;

using trianglef2 = trianglef<2>;
using trianglef3 = trianglef<3>;

// maybe error in editor, but no compile error
static_assert(sizeof(trianglef3) == 9 * sizeof(float));
}  // namespace My

#include "detail/triangle.inl"
