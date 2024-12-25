//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../IMul.h"
#include "IMatrix.h"

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
    Impl rst{};
    for (size_t col = 0; col < N; col++) {
      for (size_t row = 0; row < N; row++) {
        F val{};
        for (size_t i = 0; i < N; i++)
          val += x[i][row] * y[col][i];
        rst[col][row] = val;
      }
    }
    return rst;
  }
};
}  // namespace My
