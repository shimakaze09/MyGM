//
// Created by Admin on 25/12/2024.
//

#pragma once

#include <MyTemplate/SI.h>

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IMetric : Base {
  using T = At_t<ArgList, 0>;

  using Base::Base;

  static T distance(const Impl& x, const Impl& y) noexcept {
    return Impl::impl_distance(x, y);
  }

  T distance(const Impl& y) const noexcept {
    const Impl& x = static_cast<const Impl&>(*this);
    return x.distance(y);
  }
};
}  // namespace My
