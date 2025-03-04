//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../IMul.h"
#include "IMatrix.h"
#include "IMatrixMul_detail.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IMatrixMul : Base {
  using IList = TemplateList<IMul, IMatrix>;
  using Base::Base;

  static constexpr size_t N = Arg_N<ArgList>;
  using F = Arg_F<ArgList>;

  using Base::operator*;

  using Vector = Arg_T<ArgList>;

  inline const Vector operator*(const Vector& v) const noexcept {
    auto& m = static_cast<const Impl&>(*this);
    return detail::IMatrixMul::mul<N>::run(m, v);
  }

 private:
  template <typename Base, typename Impl, typename ArgList>
  friend struct IMul;

  inline const Impl impl_mul(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return detail::IMatrixMul::mul<N>::run(x, y);
  }

  inline const Impl impl_inverse() const noexcept {
    auto& m = static_cast<const Impl&>(*this);
    return detail::IMatrixMul::inverse<N>::run(m);
  }
};
}  // namespace My