#pragma once

#include "IAffineSubspace.hpp"

namespace Smkz {
template <typename Base, typename Point>
struct IAffine : Base {
  using Base::Base;

  using Base::operator-;

  using Vector = SI_ImplTraits_V<Point>;

  static_assert(SI_Contains_v<Vector, ILinear>);

  const Vector operator-(const Point& y) const noexcept {
    return static_cast<const Point*>(this)->impl_affine_minus(y);
  }
};
}  // namespace  Smkz

SI_InterfaceTraits_Register(Smkz::IAffine, Smkz::IAffineSubspace);
