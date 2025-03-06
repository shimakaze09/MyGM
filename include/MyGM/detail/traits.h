//
// Created by Admin on 6/03/2025.
//

#pragma once

#include <MyTemplate/SI.h>
#include "forward_decl.h"

namespace My {
template <typename T_, size_t N_, typename F_>
struct ArrayTraits {
  using T = T_;
  static constexpr size_t N = N_;
  using F = F_;
};

template <typename T, size_t N>
struct Array1DTraits : ArrayTraits<T, N, T> {};

template <template <typename, typename> class... Interfaces>
struct IListTraits {
  using IList = TemplateList<Interfaces...>;
};

template <bool support>
struct SIMDTraits {
  static constexpr bool support_SIMD = support;
};
}  // namespace My
