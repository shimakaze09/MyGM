//
// Created by Admin on 25/12/2024.
//

#pragma once

namespace My {
template <typename Base, typename Impl>
struct IMul : Base {
  using Base::Base;

  using Base::operator*;

  inline const Impl operator*(const Impl& y) const noexcept {
    return static_cast<const Impl*>(this)->impl_mul(y);
  }

  // it's necessary to distinguish left mul and right mul
  // so we won't provide operator*=
  // Impl& operator*=(const Impl& y) noexcept {
  //   return static_cast<Impl*>(this)->impl_add_to_self(y);
  // }

  inline const Impl inverse() const noexcept {
    return static_cast<const Impl*>(this)->impl_inverse();
  }
};
}  // namespace My
