//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../../basic.h"
#include "../IInOut.h"
#include "IArray.h"

#include <MyTemplate/SI.h>

namespace My {
template <typename Base, typename Impl>
struct IArrayInOut : Base {
  using Base::Base;

  static constexpr size_t N = ImplTraits_N<Impl>;

  std::ostream& impl_out(std::ostream& os) const noexcept {
    auto& x = static_cast<const Impl&>(*this);

    for (size_t i = 0; i < N - 1; i++)
      os << rmv_epsilon(x[i]) << " ";
    os << rmv_epsilon(x[N - 1]);

    return os;
  }

  std::istream& impl_in(std::istream& is) noexcept {
    auto& x = static_cast<Impl&>(*this);

    for (size_t i = 0; i < N; i++)
      is >> x[i];

    return is;
  }
};

InterfaceTraits_Regist(IArrayInOut, IArray, IInOut);
}  // namespace My
