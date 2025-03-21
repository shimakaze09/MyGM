//
// Created by Admin on 29/12/2024.
//

#pragma once

#include "IAffineRealSubspace.h"
#include "IOLine.h"

namespace My {
// line in real affine subspace
template <typename Base, typename Impl>
struct ILine : Base {
  using Base::Base;

  using Point = ImplTraits_P<Impl>;
  using Vector = ImplTraits_V<Impl>;
  using F = ImplTraits_F<Impl>;

  void init_ILine(const Point& p, const Vector& dir) noexcept {
    this->init_IAffineRealSubspace(p);
    this->init_IOLine(dir);
  }

  const Point at(F t) const noexcept { return this->point + t * this->dir; }
};

InterfaceTraits_Register(ILine, IAffineRealSubspace, IOLine);
}  // namespace My