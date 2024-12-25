//
// Created by Admin on 25/12/2024.
//

#pragma once

#include <array>
#include <iostream>

#include <assert.h>
#include <cmath>

namespace My {
template <typename Base, typename Impl, typename T, typename N>
struct IVal : Base, std::array<T, N::value> {
  static_assert(std::is_same_v<typename N::type, size_t>,
                "N::type isn't size_t");
  static_assert(N::value > 0, "N::value > 0");
  static_assert(std::is_arithmetic_v<T>, "std::is_arithmetic_v<T>");

  using Base::Base;
  using value_type = T;

  IVal() {}

  template <typename... U>
  IVal(U... data) : std::array<T, N::value>{static_cast<T>(data)...} {
    static_assert(sizeof...(U) == N::value, "sizeof...(U) == N::value");
  }

  const Impl Abs() const {
    Impl rst{};
    for (size_t i = 0; i < N::value; i++)
      rst[i] = std::abs((*this)[i]);
    return rst;
  }

  bool HasNaN() const noexcept {
    for (size_t i = 0; i < N::value; i++) {
      if (std::isnan<float>(static_cast<float>((*this)[i])))
        return true;
    }
    return false;
  }

  const T& MinComponent() const noexcept { return (*this)[MinDim()]; }

  const T& MaxComponent() const noexcept { return (*this)[MaxDim()]; }

  constexpr size_t MinDim() const noexcept {
    T minVal = (*this)[0];
    size_t minDim = 0;
    for (size_t i = 1; i < N::value; i++) {
      if ((*this)[i] < minVal) {
        minVal = (*this)[i];
        minDim = i;
      }
    }
    return minDim;
  }

  constexpr size_t MaxDim() const noexcept {
    T maxVal = (*this)[0];
    size_t maxDim = 0;
    for (size_t i = 1; i < N::value; i++) {
      if ((*this)[i] < maxVal) {
        maxVal = (*this)[i];
        maxDim = i;
      }
    }
    return maxDim;
  }

  friend std::ostream& operator<<(std::ostream& os, const Impl& x) {
    // for-loop will be optimized in -02 (release)
    for (auto i = static_cast<size_t>(0); i < N::value - 1; i++)
      os << x[i] << ",";
    os << x[N::value - 1];
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Impl& x) {
    // for-loop will be optimized in -02 (release)
    for (auto i = static_cast<size_t>(0); i < N::value; i++)
      is >> x[i];
    return is;
  }
};
}  // namespace My