//
// Created by Admin on 27/12/2024.
//

#pragma once

#include "IArray.h"
#include "IArray1D.h"

namespace My {
template <typename Base, typename Impl>
struct IArrayCast : Base {
  using Base::Base;

  static constexpr size_t N = ImplTraits_N<Impl>;

  template <typename To>
  const To cast_to() const noexcept {
    constexpr size_t M = To::N;
    static_assert(M <= N &&
                  SI_Contains_v<Impl, IArray1D> == SI_Contains_v<To, IArray1D>);
    return cast_to<To>(std::make_index_sequence<M>{});
  }

  // reinterpret cast
  template <typename To>
  To& as() & noexcept {
    static_assert(sizeof(To) == sizeof(Impl)
                  // && std::is_same_v<ImplTraits_T<To>, ImplTraits_T<Impl>>
                  && alignof(Impl) >= alignof(To));
    return reinterpret_cast<To&>(*this);
  }

  template <typename To>
  const To& as() const& noexcept {
    return const_cast<IArrayCast*>(this)->as<To>();
  }

 private:
  template <typename To, size_t... Ns>
  const To cast_to(std::index_sequence<Ns...>) const noexcept {
    return {static_cast<typename To::T>((*this)[Ns])...};
  }
};

InterfaceTraits_Register(IArrayCast, IArray);
}  // namespace My
