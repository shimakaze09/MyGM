#pragma once

#include "IArrayCast.hpp"
#include "IArrayInOut.hpp"

namespace Smkz {
template <typename Base, typename Impl>
struct IArrayUtil : Base {
  using Base::Base;

  using T = SI_ImplTraits_T<Impl>;
  static constexpr size_t N = SI_ImplTraits_N<Impl>;
  using F = SI_ImplTraits_F<Impl>;

  Impl rmv_epsilon() const noexcept {
    Impl rst;
    for (size_t i = 0; i < N; i++) rst[i] = Smkz::rmv_epsilon((*this)[i]);
    return rst;
  }

  bool is_all_zero() const noexcept {
    for (size_t i = 0; i < N; i++) {
      if (is_zero((*this)[i])) return false;
    }
    return true;
  }

  bool has_nan() const noexcept {
    for (size_t i = 0; i < N; i++) {
      if (is_nan((*this)[i])) return true;
    }
    return false;
  }

  static Impl lerp(const Impl& x, const Impl& y, F t) noexcept {
    F one_minus_t = static_cast<F>(1) - t;
#ifdef SMKZ_USE_SIMD
    if constexpr (SI_ImplTraits_SupportSIMD<Impl>)
      return _mm_add_ps(_mm_mul_ps(x, _mm_set1_ps(one_minus_t)),
                        _mm_mul_ps(y, _mm_set1_ps(t)));
    else
#endif  // SMKZ_USE_SIMD
    {
      Impl rst;
      for (size_t i = 0; i < N; i++) rst[i] = Smkz::lerp(x[i], y[i], t);
      return rst;
    }
  }

  Impl lerp(const Impl& y, F t) const noexcept {
    const auto& x = static_cast<const Impl&>(*this);
    return lerp(x, y, t);
  }

  static Impl mid(const Impl& x, const Impl& y) noexcept {
    return lerp(x, y, static_cast<F>(0.5));
  }

  template <typename ValContainer, typename WeightContainer>
  static Impl mix(const ValContainer& vals,
                  const WeightContainer& weights) noexcept {
    assert(vals.size() > 0 && vals.size() == weights.size());
    auto val_iter = vals.begin();
    auto weight_iter = weights.begin();

#ifdef SMKZ_USE_SIMD
    if constexpr (SI_ImplTraits_SupportSIMD<Impl>) {
      __m128 rst = _mm_mul_ps(*val_iter, *weight_iter);
      ++val_iter;
      ++weight_iter;
      while (val_iter != vals.end()) {
        rst = _mm_add_ps(rst, _mm_mul_ps(*val_iter, *weight_iter));
        ++val_iter;
        ++weight_iter;
      }
      return rst;
    } else
#endif  // SMKZ_USE_SIMD
    {
      Impl rst;
      for (size_t j = 0; j < N; j++) rst[j] = (*val_iter)[j] * (*weight_iter);
      while (val_iter != vals.end()) {
        for (size_t j = 0; j < N; j++)
          rst[j] += (*val_iter)[j] * (*weight_iter);
        ++val_iter;
        ++weight_iter;
      }
      return rst;
    }
  }
};
}  // namespace  Smkz

SI_InterfaceTraits_Register(Smkz::IArrayUtil, Smkz::IArrayCast,
                            Smkz::IArrayInOut);
