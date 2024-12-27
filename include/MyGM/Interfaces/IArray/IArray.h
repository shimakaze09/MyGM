//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../../basic.h"
#include "../Arg.h"

#include <MyTemplate/SI.h>

#include <array>
#include <iostream>

#include <assert.h>
#include <cmath>

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IArray
    : Base,
      std::array<At_t<At_t<ArgList, 0>, 0>, At_t<At_t<ArgList, 0>, 1>::value> {
 private:
  using Base::operator[];

 public:
  using std::array<At_t<At_t<ArgList, 0>, 0>,
                   At_t<At_t<ArgList, 0>, 1>::value>::operator[];

 public:
  using T = Arg_T<ArgList>;
  static constexpr size_t N = Arg_N<ArgList>;
  using F = Arg_F<ArgList>;
  static_assert(N > 0);
  // static_assert(std::is_arithmetic_v<F>);

  using Base::Base;
  using std::array<At_t<At_t<ArgList, 0>, 0>,
                   At_t<At_t<ArgList, 0>, 1>::value>::array;

  IArray() {}

  template <typename... U,
            typename = std::enable_if_t<(std::is_convertible_v<U, T> && ...)>>
  inline IArray(U... data) : std::array<T, N>{static_cast<T>(data)...} {
    static_assert(sizeof...(U) == N);
  }

  inline const Impl rmv_epsilon() const noexcept {
    Impl rst{};
    for (size_t i = 0; i < N; i++)
      rst[i] = My::rmv_epsilon((*this)[i]);
    return rst;
  }

  inline bool is_all_zero() const noexcept {
    for (size_t i = 0; i < N; i++) {
      if (is_zero((*this)[i]))
        return false;
    }
    return true;
  }

  inline bool has_nan() const noexcept {
    for (size_t i = 0; i < N; i++) {
      if (is_nan((*this)[i]))
        return true;
    }
    return false;
  }

  inline const Impl lerp(const Impl& y, F t) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    Impl rst{};
    F one_minus_t = static_cast<F>(1) - t;
    for (size_t i = 0; i < N; i++)
      rst[i] = x[i] * one_minus_t + y[i] * t;
    return rst;
  }
};
}  // namespace My