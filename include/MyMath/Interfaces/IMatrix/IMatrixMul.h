//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../IMul.h"
#include "IMatrix.h"
#include "IMatrixMul_detail.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IMatrixMul
    : SIVT_CRTP<TemplateList<IMul, IMatrix>, Base, Impl, ArgList> {
  static constexpr size_t N = Arg_N<ArgList>;
  using F = Arg_F<ArgList>;
  using SIVT_CRTP<TemplateList<IMul, IMatrix>, Base, Impl, ArgList>::SIVT_CRTP;
  using SIVT_CRTP<TemplateList<IMul, IMatrix>, Base, Impl, ArgList>::operator*;

 private:
  template <typename Base, typename Impl, typename ArgList>
  friend struct IMul;

  const Impl impl_mul(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return detail::IMatrix::run_mul(x, y);
  }

  const Impl impl_inverse() const noexcept {
    auto& m = static_cast<const Impl&>(*this);
    return detail::IMatrix::run_inverse(m);
  }
};
}  // namespace My
