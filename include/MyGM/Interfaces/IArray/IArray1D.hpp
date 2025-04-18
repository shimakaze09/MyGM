#pragma once

#include "IArray.hpp"

namespace My {
template <typename Base, typename Impl>
struct IArray1D : Base {
  using Base::Base;
  static_assert(!SI_Contains_v<SI_ImplTraits_T<Impl>, IArray>);
};
}  // namespace My

SI_InterfaceTraits_Register(My::IArray1D, My::IArray);
