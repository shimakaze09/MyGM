//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "INorm.h"

#include <cassert>

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IInnerProduct : SIVT_CRTP<TemplateList<INorm>, Base, Impl, ArgList> {
  using T = At_t<ArgList, 0>;

  using SIVT_CRTP<TemplateList<INorm>, Base, Impl, ArgList>::SIVT_CRTP;

  static T dot(const Impl& x, const Impl& y) noexcept {
    return Impl::impl_dot(x, y);
  }

  T dot(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return dot(x, y);
  }

  T norm2() const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return dot(x, x);
  }

  static T distance2(const Impl& x, const Impl& y) noexcept {
    return (x - y).norm2();
  }

  T distance2(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return distance2(x, y);
  }

  // radian
  static T angle(const Impl& x, const Impl& y) noexcept {
    T xN = x.norm();
    T yN = y.norm();
    T xyN = xN * yN;
    assert(xyN != static_cast<T>(0));
    return Impl::dot(x, y) / xyN;
  }

  T angle(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return angle(x, y);
  }

 private:
  template<typename Base, typename Impl, typename ArgList>
  friend struct INorm;

  T impl_norm() const noexcept { return std::sqrt(norm2()); }
};
}  // namespace My
