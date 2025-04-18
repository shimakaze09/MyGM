#pragma once

#include "IAffineRealSubspace.hpp"
#include "IOLine.hpp"

namespace Smkz {
// line in real affine subspace
template <typename Base, typename Impl>
struct ILine : Base {
  using Base::Base;

  using Point = SI_ImplTraits_P<Impl>;
  using Vector = SI_ImplTraits_V<Impl>;
  using F = SI_ImplTraits_F<Impl>;

  Point at(F t) const noexcept { return this->point + t * this->dir; }
};
}  // namespace  Smkz

SI_InterfaceTraits_Register(Smkz::ILine, Smkz::IAffineRealSubspace,
                            Smkz::IOLine);