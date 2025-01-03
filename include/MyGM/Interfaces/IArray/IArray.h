//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../../basic.h"
#include "../Arg.h"

#include <MyTemplate/SI.h>

#include <array>
#include <iostream>
#include <vector>

#include <cassert>
#include <cmath>

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IArray : Base, std::array<Arg_T<ArgList>, Arg_N<ArgList>> {
 private:
  using Base::operator[];

 public:
  using std::array<Arg_T<ArgList>, Arg_N<ArgList>>::operator[];

 public:
  using T = Arg_T<ArgList>;
  static constexpr size_t N = Arg_N<ArgList>;
  using F = Arg_F<ArgList>;
  static_assert(N > 0);

  using Base::Base;
  using std::array<Arg_T<ArgList>, Arg_N<ArgList>>::array;

  IArray() noexcept {}

  constexpr IArray(T t) noexcept {
    for (size_t i = 0; i < N; i++)
      (*this)[i] = T{t};
  }

  template <typename... U,
            typename = std::enable_if_t<(std::is_convertible_v<U, T> && ...)>>
  constexpr IArray(U... data) noexcept
      : std::array<T, N>{static_cast<T>(data)...} {
    static_assert(sizeof...(U) == N, "number of parameters is not correct");
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

  static const Impl lerp(const Impl& x, const Impl& y, F t) noexcept {
    Impl rst{};
    F one_minus_t = static_cast<F>(1) - t;
    for (size_t i = 0; i < N; i++)
      rst[i] = My::lerp(x[i], y[i], t);
    return rst;
  }

  inline const Impl lerp(const Impl& y, F t) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return lerp(x, y, t);
  }

  static const Impl mid(const Impl& x, const Impl& y) noexcept {
    return lerp(x, y, static_cast<F>(0.5));
  }

  static const Impl mix(const std::vector<Impl>& vals,
                        const std::vector<float>& weights) noexcept {
    assert(vals.size() > 0 && vals.size() == weights.size());
    Impl rst{};
    for (size_t j = 0; j < N; j++)
      rst[j] = vals[0][j] * weights[0];
    for (size_t i = 1; i < vals.size(); i++) {
      for (size_t j = 0; j < N; j++)
        rst[j] += vals[i][j] * weights[i];
    }
    return rst;
  }
};
}  // namespace My