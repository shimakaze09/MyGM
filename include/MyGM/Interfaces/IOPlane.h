//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "ILinear.h"

#include <tuple>

namespace My {
// plane in linear subspace
// 'O' : original point
template <typename Base, typename Impl>
struct IOPlane : Base {
  using Base::Base;

  using Vector = ImplTraits_V<Impl>;
  using F = ImplTraits_F<Impl>;

  static_assert(Vector::template Contains<ILinear>());

  ImplTraits_V<Impl> normal;

  void init_IOPlane(const Vector& n) noexcept { normal = n; }
};
}  // namespace My
