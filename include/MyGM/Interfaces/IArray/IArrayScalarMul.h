//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../IScalarMul.h"
#include "IArray.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IArrayScalarMul
    : SIVT_CRTP<TemplateList<IScalarMul, IArray>, Base, Impl, ArgList> {
  static constexpr size_t N = Arg_N<ArgList>;
  using F = Arg_F<ArgList>;
  using T = Arg_T<ArgList>;

  using SIVT_CRTP<TemplateList<IScalarMul, IArray>, Base, Impl,
                  ArgList>::SIVT_CRTP;
  using SIVT_CRTP<TemplateList<IScalarMul, IArray>, Base, Impl,
                  ArgList>::operator*;

 private:
  template <typename Base, typename Impl, typename ArgList>
  friend struct IScalarMul;

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  inline const Impl impl_scalar_mul(U k) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    auto kF = static_cast<F>(k);
    Impl rst{};

#ifdef USE_XSIMD
    if constexpr (std::is_same_v<T, float> && N == 4) {
      auto sx = xsimd::load_aligned(x.data());
      auto srst = sx * kF;
      srst.store_aligned(rst.data());
    } else
#endif  // USE_XSIMD
      for (size_t i = 0; i < N; i++)
        rst[i] = x[i] * kF;
    return rst;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  inline Impl& impl_scalar_mul_to_self(U k) noexcept {
    auto& x = static_cast<Impl&>(*this);
    auto kF = static_cast<F>(k);
#ifdef USE_XSIMD
    if constexpr (std::is_same_v<T, float> && N == 4) {
      auto sx = xsimd::load_aligned(x.data());
      sx *= kF;
      sx.store_aligned(x.data());
    } else
#endif  // USE_XSIMD
      for (size_t i = 0; i < N; i++)
        x[i] *= kF;
    return x;
  }
};
}  // namespace My
