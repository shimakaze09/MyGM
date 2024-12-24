//
// Created by Admin on 25/12/2024.
//

#pragma once

#include <array>
#include <iostream>

#include <assert.h>

namespace My {
template <typename Base, typename Impl, typename T, typename N>
struct IVal : Base, std::array<T, N::value> {
  using Base::Base;

  IVal() {}

  template <typename... U>
  IVal(U... data) : std::array<T, N::value>{static_cast<T>(data)...} {
    static_assert(sizeof...(U) == N::value, "sizeof...(U) == N::value");
  }

  friend std::ostream& operator<<(std::ostream& os, const Impl& x) {
    // for-loop will be optimized in -02 (release)
    for (auto i = static_cast<typename N::type>(0); i < N::value - 1; i++)
      os << x[i] << ",";
    os << x[N::value - 1];
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Impl& x) {
    // for-loop will be optimized in -02 (release)
    for (auto i = static_cast<typename N::type>(0); i < N::value; i++)
      is >> x[i];
    return is;
  }
};
}  // namespace My