//
// Created by Admin on 25/12/2024.
//

#pragma once

#include <MyTemplate/SI.h>
#include "../IMul.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IArrayHadamardProduct
    : SIVT_CRTP<TemplateList<IMul>, Base, Impl, ArgList> {
  using F = Arg_F<ArgList>;
  static constexpr size_t N = Arg_N<ArgList>;

  using SIVT_CRTP<TemplateList<IMul>, Base, Impl, ArgList>::SIVT_CRTP;

 private:
  template <typename Base, typename Impl, typename ArgList>
  friend struct IMul;

  const Impl impl_mul(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);

    Impl rst{};

    for (size_t i = 0; i < N; i++)
      rst[i] = x[i] * y[i];

    return rst;
  }

  const Impl inverse() const noexcept {
    auto& x = static_cast<const Impl&>(*this);

    Impl rst{};

    for (size_t i = 0; i < N; i++)
      rst[i] = static_cast<F>(1) / x[i];

    return rst;
  }
};
}  // namespace My
