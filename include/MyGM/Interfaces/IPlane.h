//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "IAffineRealSubspace.h"
#include "IOPlane.h"

namespace My {
// plane in real affine subspace
template <typename Base, typename Impl>
struct IPlane : Base {
  using Base::Base;

  using Point = ImplTraits_P<Impl>;
  using Vector = ImplTraits_V<Impl>;

  void init_IPlane(const Point& p, const Vector& n) noexcept {
    this->init_IAffineRealSubspace(p);
    this->init_IOPlane(n);
  }
};

InterfaceTraits_Regist(IPlane, IAffineRealSubspace, IOPlane);
}  // namespace My
