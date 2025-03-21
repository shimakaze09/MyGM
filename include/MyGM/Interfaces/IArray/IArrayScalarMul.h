//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../IScalarMul.h"
#include "IArray.h"

namespace My {
template <typename Base, typename Impl>
struct IArrayScalarMul : Base {
  using Base::Base;

  using T = ImplTraits_T<Impl>;
  static constexpr size_t N = ImplTraits_N<Impl>;
  using F = ImplTraits_F<Impl>;

#ifdef MY_USE_SIMD
  using Base::operator*;
  using Base::operator*=;
  using Base::operator/;
  using Base::operator/=;

  inline bool is_scalar() const noexcept {
    static_assert(ImplTraits_SupportSIMD<Impl>);
    const auto& x = static_cast<const Impl&>(*this);
    return x == x.replicate<0>();
  }

  inline Impl operator*(const __m128& k) const noexcept {
    static_assert(ImplTraits_SupportSIMD<Impl>);
    const auto& x = static_cast<const Impl&>(*this);
    assert(Impl{k}.is_scalar() || x.is_scalar());
    return _mm_mul_ps(x, k);
  }

  inline Impl& operator*=(const __m128& k) noexcept {
    const auto& x = static_cast<const Impl&>(*this);
    return x = x * k;
  }

  inline Impl operator/(const __m128& k) const noexcept {
    static_assert(ImplTraits_SupportSIMD<Impl>);
    const auto& x = static_cast<const Impl&>(*this);
    assert(Impl{k}.is_scalar());
    return _mm_div_ps(x, k);
  }

  inline Impl& operator/=(const __m128& k) noexcept {
    const auto& x = static_cast<const Impl&>(*this);
    return x = x / k;
  }
#endif  // MY_USE_SIMD

 private:
  template <typename Base, typename Impl>
  friend struct IScalarMul;

  inline Impl impl_scalar_mul(F k) const noexcept {
    const auto& x = static_cast<const Impl&>(*this);
#ifdef MY_USE_SIMD
    if constexpr (ImplTraits_SupportSIMD<Impl>)
      return _mm_mul_ps(x, Impl{k});
    else
#endif  // MY_USE_SIMD
    {
      Impl rst;
      for (size_t i = 0; i < N; i++)
        rst[i] = x[i] * k;
      return rst;
    }
  }

  inline Impl& impl_scalar_mul_to_self(F k) noexcept {
    auto& x = static_cast<Impl&>(*this);
#ifdef MY_USE_SIMD
    if constexpr (ImplTraits_SupportSIMD<Impl>)
      return x = x * k;
    else
#endif  // MY_USE_SIMD
    {
      for (size_t i = 0; i < N; i++)
        x[i] *= k;
      return x;
    }
  }
};

InterfaceTraits_Register(IArrayScalarMul, IScalarMul, IArray);
}  // namespace My
