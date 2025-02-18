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
  using Vector = Arg_Vector<ArgList>;
  using F = Arg_F<ArgList>;

  static_assert(ExistInstance_v<typename Vector::AllVBs, ILinear>);

  Arg_Vector<ArgList> dir;

  void init_IOLine(const Vector& v) noexcept { dir = v; }
};
}  // namespace My