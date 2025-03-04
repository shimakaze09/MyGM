//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "ILinear.h"

#include <tuple>

namespace My {
// line in linear subspace
// 'O' : original point
template <typename Base, typename Impl, typename ArgList>
struct IOLine : Base {
  using Base::Base;

  using Vector = Arg_Vector<ArgList>;
  using F = Arg_F<ArgList>;

  static_assert(Vector::template IsContain<ILinear>());

  Arg_Vector<ArgList> dir;

  Arg_Vector<ArgList> inv_dir() const noexcept {
#ifdef MY_USE_XSIMD
    if constexpr (std::is_same_v<F, float> && Arg_Vector<ArgList>::N == 4)
      return 1.f / (*this).get_batch();
    else
#endif
    {
      Arg_Vector<ArgList> rst;
      for (size_t i = 0; i < Arg_Vector<ArgList>::N; i++)
        rst[i] = ONE<F> / dir[i];
      return rst;
    }
  }

  void init_IOLine(const Vector& v) noexcept { dir = v; }
};
}  // namespace My