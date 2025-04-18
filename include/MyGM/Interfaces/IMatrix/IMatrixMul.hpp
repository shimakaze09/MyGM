#pragma once

#include "../IMul.hpp"
#include "IMatrix.hpp"
#include "details/IMatrixMul.inl"

namespace My {
template <typename Base, typename Impl>
struct IMatrixMul : Base {
  using Base::Base;

  static constexpr size_t N = SI_ImplTraits_N<Impl>;
  using F = SI_ImplTraits_F<Impl>;

  using Base::operator*;

  using Vector = SI_ImplTraits_T<Impl>;

  const Vector operator*(const Vector& v) const noexcept {
    auto& m = static_cast<const Impl&>(*this);
    return details::IMatrixMul::mul<N>::run(m, v);
  }

 private:
  template <typename, typename>
  friend struct IMul;

  Impl impl_mul(const Impl& y) const noexcept {
    const auto& x = static_cast<const Impl&>(*this);
    return details::IMatrixMul::mul<N>::run(x, y);
  }

  Impl impl_inverse() const noexcept {
    auto& m = static_cast<const Impl&>(*this);
    return details::IMatrixMul::inverse<N>::run(m);
  }
};
}  // namespace My

SI_InterfaceTraits_Register(My::IMatrixMul, My::IMul, My::IMatrix);
