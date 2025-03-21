//
// Created by Admin on 6/03/2025.
//

#pragma once

#include <MyTemplate/SI.h>

namespace My::details::ImplTraits_ {
template <typename Impl>
struct ImplTraits_SupportSIMD;
}  // namespace My::details::ImplTraits_

namespace My {
// element type
template <typename Impl>
using ImplTraits_T = typename ImplTraits<Impl>::T;

// element num
template <typename Impl>
constexpr size_t ImplTraits_N = ImplTraits<Impl>::N;

// number field
template <typename Impl>
using ImplTraits_F = typename ImplTraits<Impl>::F;

// vector
template <typename Impl>
using ImplTraits_V = typename ImplTraits<Impl>::V;

// point
template <typename Impl>
using ImplTraits_P = typename ImplTraits<Impl>::P;

template <typename Impl>
constexpr bool ImplTraits_SupportSIMD =
    details::ImplTraits_::ImplTraits_SupportSIMD<Impl>::value;
}  // namespace My

namespace My::details::ImplTraits_ {
#ifdef MY_USE_SIMD
template <typename Enabler, typename Impl>
struct ImplTraits_SupportSIMD_Helper : std::true_type {};

template <typename Impl>
struct ImplTraits_SupportSIMD_Helper<
    std::enable_if_t<!ImplTraits<Impl>::support_SIMD>, Impl> : std::false_type {
};

template <typename Impl>
struct ImplTraits_SupportSIMD
    : IValue<bool, ImplTraits_SupportSIMD_Helper<void, Impl>::value &&
                       std::is_same_v<ImplTraits_T<Impl>, float> &&
                       ImplTraits_N<Impl> == 4> {};
#else
template <typename Impl>
struct ImplTraits_SupportSIMD : std::false_type {};
#endif
}  // namespace My::details::ImplTraits_
