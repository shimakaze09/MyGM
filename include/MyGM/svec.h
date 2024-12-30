//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "mat.h"

namespace My {
// vector in surface coordinate system (right-hand)
// most functions assert(normalized())
// x: tangent
// y: bitangent
// z: normal
// stheta : angle between vector and normal [0 - pi]
// sphi : angle between vector and tangent [0 - 2pi]
template <typename T>
struct svec : SIIT_CRTP<TemplateList<IArray1D_Util, ICross>, svec<T>,
                        TypeList<TypeList<T, Size<3>>, T>> {
  using SIIT_CRTP<TemplateList<IArray1D_Util, ICross>, svec<T>,
                  TypeList<TypeList<T, Size<3>>, T>>::SIIT_CRTP;

  // TBN matrix : local(surface) to world
  // require: n is perpendicular to t
  static const mat<T, 3> TBN(const vec<T, 3>& n, const vec<T, 3>& t) noexcept;

  static const svec mid(const svec<T>& x, const svec<T>& y) noexcept;

  T cos_stheta() const noexcept;

  T sin_stheta() const noexcept;

  // if this is normal, return 1
  T cos_sphi() const noexcept;

  // if this is normal, return 0
  T sin_sphi() const noexcept;

  // [summary]
  // this is inward direction (outward from surface), maybe under surface
  // reflected direction is outward direction (outward from surface) on the same side
  // [return]
  // - outward (this->norm() == result.norm())
  const svec reflect() const noexcept;

  // [summary]
  // this is inward direction (outward from surface), maybe under surface
  // refracted direction is outward direction (outward from surface) on the other side
  // total reflection may occur
  // [argument]
  // - etai : refractive index of [inward(this)] side
  // - etao : refractive index of [outward] side
  // [return]
  // - bool: whether refract is success
  // - svec: normalized outward
  const std::tuple<bool, svec> refract(T etai, T etao) const noexcept;
};

// local to world
// m is generated by svec<T>::TBN()
template <typename T>
const vec<T, 3> operator*(const mat<T, 3>& m, const svec<T>& sv) noexcept;

using svecf = svec<float>;
}  // namespace My

#include "detail/svec.inl"