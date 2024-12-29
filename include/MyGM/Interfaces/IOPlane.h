//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "ILinear.h"

#include <tuple>

namespace My {
// plane in linear subspace
// 'O' : original point
template <typename Base, typename Impl, typename ArgList>
struct IOPlane : std::tuple<Arg_Vector<ArgList>>, Base {
  using Vector = Arg_Vector<ArgList>;
  using F = Arg_F<ArgList>;

  static_assert(ExistInstance_v<typename Vector::AllVBs, ILinear>);

  using Base::Base;
  using std::tuple<Arg_Vector<ArgList>, Arg_Vector<ArgList>>::tuple;

  Vector& normal() noexcept { return std::get<Vector>(*this); }

  const Vector& normal() const noexcept { return std::get<Vector>(*this); }

  void init_IOPlane(const Vector& n) noexcept { normal() = n; }
};
}  // namespace My
