#pragma once

#include <MyTemplate/SI.hpp>

#include "../../basic.hpp"
#include "../IInOut.hpp"
#include "IMatrix.hpp"

namespace My {
template <typename Base, typename Impl>
struct IMatrixInOut : Base {
  using Base::Base;

  static constexpr size_t N = SI_ImplTraits_N<Impl>;

  void print(std::ostream& os = std::cout) const noexcept {
    const auto& x = static_cast<const Impl&>(*this);

    for (size_t row = 0; row < N; row++) {
      for (size_t col = 0; col < N - 1; col++)
        os << rmv_epsilon(x[col][row]) << " ";
      os << rmv_epsilon(x[N - 1][row]) << std::endl;
    }
  }
};
}  // namespace  My

SI_InterfaceTraits_Register(My::IMatrixInOut, My::IMatrix);