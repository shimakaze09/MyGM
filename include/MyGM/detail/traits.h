//
// Created by Admin on 6/03/2025.
//

#pragma once

#include <MyTemplate/SI.h>
#include "forward_decl.h"

namespace My {
template <typename T_, size_t N_>
struct ArrayTraits {
  using T = T_;
  static constexpr size_t N = N_;
};
}  // namespace My
