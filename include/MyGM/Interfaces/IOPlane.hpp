#pragma once

#include <tuple>

#include "ILinear.hpp"

namespace Smkz {
// plane in linear subspace
// 'O' : original point
template <typename Base, typename Impl>
struct IOPlane : Base {
  using Base::Base;

  using Normal = SI_ImplTraits_V<Impl>;
  using F = SI_ImplTraits_F<Impl>;

  static_assert(SI_Contains_v<Normal, ILinear>);

  SI_ImplTraits_V<Impl> normal;
};
}  // namespace  Smkz
