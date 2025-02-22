//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../IAdd.h"
#include "IArray.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IArrayAdd : SIVT_CRTP<TemplateList<IAdd, IArray>, Base, Impl, ArgList> {
  static constexpr size_t N = Arg_N<ArgList>;
  using T = Arg_T<ArgList>;

  using SIVT_CRTP<TemplateList<IAdd, IArray>, Base, Impl, ArgList>::SIVT_CRTP;

 private:
  template <typename Base, typename Impl, typename ArgList>
  friend struct IAdd;

  inline const Impl impl_add(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    Impl rst{};
#ifdef USE_XSIMD
    if constexpr (std::is_same_v<T, float> && N == 4) {
      auto sx = xsimd::load_aligned(x.data());
      auto sy = xsimd::load_aligned(y.data());
      auto srst = sx + sy;
      srst.store_aligned(rst.data());
    } else
#endif  // USE_XSIMD
      for (size_t i = 0; i < N; i++)
        rst[i] = x[i] + y[i];
    return rst;
  }

  inline Impl& impl_add_to_self(const Impl& y) noexcept {
    auto& x = static_cast<Impl&>(*this);
#ifdef USE_XSIMD
    if constexpr (std::is_same_v<T, float> && N == 4) {
      auto sx = xsimd::load_aligned(x.data());
      auto sy = xsimd::load_aligned(y.data());
      sx += sy;
      sx.store_aligned(x.data());
    } else
#endif  // USE_XSIMD
      for (size_t i = 0; i < N; i++)
        x[i] += y[i];
    return x;
  }

  inline const Impl impl_add_inverse() const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    Impl rst{};
#ifdef USE_XSIMD
    if constexpr (std::is_same_v<T, float> && N == 4) {
      auto sx = xsimd::load_aligned(x.data());
      auto srst = -sx;
      srst.store_aligned(rst.data());
    } else
#endif  // USE_XSIMD
      for (size_t i = 0; i < N; i++)
        rst[i] = -x[i];
    return rst;
  }

  inline const Impl impl_minus(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    Impl rst{};
#ifdef USE_XSIMD
    if constexpr (std::is_same_v<T, float> && N == 4) {
      auto sx = xsimd::load_aligned(x.data());
      auto sy = xsimd::load_aligned(y.data());
      auto srst = sx - sy;
      srst.store_aligned(rst.data());
    } else
#endif  // USE_XSIMD
      for (size_t i = 0; i < N; i++)
        rst[i] = x[i] - y[i];
    return rst;
  }

  inline Impl& impl_minus_to_self(const Impl& y) noexcept {
    auto& x = static_cast<Impl&>(*this);
#ifdef USE_XSIMD
    if constexpr (std::is_same_v<T, float> && N == 4) {
      auto sx = xsimd::load_aligned(x.data());
      auto sy = xsimd::load_aligned(y.data());
      sx -= sy;
      sx.store_aligned(x.data());
    } else
#endif  // USE_XSIMD
      for (size_t i = 0; i < N; i++)
        x[i] -= y[i];
    return x;
  }
};
}  // namespace My
