//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "Arg.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IMetric : Base {
  using F = Arg_F<ArgList>;

  using Base::Base;

  inline static F distance(const Impl& x, const Impl& y) noexcept {
    return Impl::impl_distance(x, y);
  }

  inline F distance(const Impl& y) const noexcept {
    const Impl& x = static_cast<const Impl&>(*this);
    return distance(x, y);
  }
};
}  // namespace My
