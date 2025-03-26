#pragma once

#include "euler.h"
#include "point.h"

#include "Interfaces/IArray/IArrayUtil.h"
#include "Interfaces/IMul.h"

namespace My {
template <typename T>
struct ImplTraits<quat<T>> : Array1DTraits<T, 4>,
                             SIMDTraits<false>,  // float4 not use SIMD
                             IListTraits<IMul, IArrayUtil> {};

template <typename T>
struct quat : SI<quat<T>> {
  using Base = SI<quat<T>>;
  using Base::Base;
  using Base::operator*;

  static const quat imag_real(const vec<T, 3>& imag, T real) noexcept;

  quat(const vec<T, 3>& axis, T theta) noexcept;

  // from and to is normalized
  quat(const vec<T, 3>& from, const vec<T, 3>& to) noexcept;

  // axis * sin(theta/2)
  vec<T, 3>& imag() noexcept;
  const vec<T, 3>& imag() const noexcept;

  // cos(thete/2)
  T& real() noexcept;
  T real() const noexcept;

  // radian
  T theta() const noexcept;
  const vec<T, 3> axis() const noexcept;

  bool is_identity() const noexcept;
  static const quat identity() noexcept;

  bool is_unit() const noexcept;

  // rotate with axis x/y/z
  // theta : radian
  // example: quatf::rotate_with<Axis::X>(to_radian(45.f))
  template <Axis axis>
  static const quat rotate_with(T theta) noexcept;

  const euler<T> to_euler() const noexcept;

  const vec<T, 3> operator*(const vec<T, 3>& v) const noexcept;

 private:
  template <typename Base, typename quat>
  friend struct IMul;

  const quat impl_mul(const quat& y) const noexcept;
  const quat impl_inverse() const noexcept;

  template <typename Base, typename quat>
  friend struct IInOut;

  std::ostream& impl_out(std::ostream& os) const noexcept;
  std::istream& impl_in(std::istream& is) noexcept;
};

using quatf = quat<float>;

// maybe error in editor, but no compile error
static_assert(sizeof(quatf) == 4 * sizeof(float));
}  // namespace My

#include "details/quat.inl"
