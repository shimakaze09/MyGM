#pragma once

#include "IArray.hpp"

namespace Smkz {
template <typename Base, typename Impl>
struct IArray1D : Base {
  using Base::Base;
  static_assert(!SI_Contains_v<SI_ImplTraits_T<Impl>, IArray>);
};
}  // namespace  Smkz

SI_InterfaceTraits_Register(Smkz::IArray1D, Smkz::IArray);
