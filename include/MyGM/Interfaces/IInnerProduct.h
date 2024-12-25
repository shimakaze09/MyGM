//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "INorm.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IInnerProduct : SIVT_CRTP<TemplateList<INorm>, Base, Impl, ArgList> {
  using F = Arg_F<ArgList>;

  using SIVT_CRTP<TemplateList<INorm>, Base, Impl, ArgList>::SIVT_CRTP;

  static F dot(const Impl& x, const Impl& y) noexcept {
    return Impl::impl_dot(x, y);
  }

  F dot(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return dot(x, y);
  }

  F norm2() const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return dot(x, x);
  }

  static F distance2(const Impl& x, const Impl& y) noexcept {
    return (x - y).norm2();
  }

  F distance2(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return distance2(x, y);
  }

  // radian
  static F cos_theta(const Impl& x, const Impl& y) noexcept {
    F xN = x.norm();
    F yN = y.norm();
    F xyN = xN * yN;
    assert(xyN != static_cast<F>(0));
    return Impl::dot(x, y) / xyN;
  }

  F cos_theta(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return cos_theta(x, y);
  }

 private:
  template <typename Base, typename Impl, typename ArgList>
  friend struct INorm;

  F impl_norm() const noexcept { return std::sqrt(norm2()); }
};
}  // namespace My
