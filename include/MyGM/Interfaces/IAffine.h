//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "IAffineSubspace.h"

namespace My {
template <typename Base, typename Point>
struct IAffine : Base {
  using Base::Base;

  using Vector = ImplTraits_V<Point>;

  static_assert(Vector::template IsContain<ILinear>());

  using Base::operator-;

  inline const Vector operator-(const Point& y) const noexcept {
    return static_cast<const Point*>(this)->impl_affine_minus(y);
  }
};

InterfaceTraits_Regist(IAffine, IAffineSubspace);
}  // namespace My
