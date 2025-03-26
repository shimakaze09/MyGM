#pragma once

#include "../../basic.h"
#include "../IInOut.h"
#include "IMatrix.h"

#include <MyTemplate/SI.h>

namespace My {
template <typename Base, typename Impl>
struct IMatrixInOut : Base {
  using Base::Base;

  static constexpr size_t N = ImplTraits_N<Impl>;

  void print(std::ostream& os = std::cout) const noexcept {
    const auto& x = static_cast<const Impl&>(*this);

    for (size_t row = 0; row < N; row++) {
      for (size_t col = 0; col < N - 1; col++)
        os << rmv_epsilon(x[col][row]) << " ";
      os << rmv_epsilon(x[N - 1][row]) << std::endl;
    }
  }
};

InterfaceTraits_Register(IMatrixInOut, IMatrix);
}  // namespace My
