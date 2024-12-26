//
// Created by Admin on 26/12/2024.
//

#pragma once

#include "euler.h"
#include "mat.h"
#include "normal.h"
#include "point.h"
#include "quat.h"
#include "scale.h"
#include "vec.h"

#include "Interfaces/IMatrix/IMatrixInOut.h"
#include "Interfaces/IMatrix/IMatrixMul.h"

namespace My {
template <typename T>
struct transform
    : SIIT_CRTP<TemplateList<IMatrixInOut, IMatrixMul>, transform<T>,
                TypeList<TypeList<vec<T, 4>, Size<4>>, T>> {
  using Base = SIIT_CRTP<TemplateList<IMatrixInOut, IMatrixMul>, transform<T>,
                         TypeList<TypeList<vec<T, 4>, Size<4>>, T>>;
  using Base::Base;
  using Base::init;
  using Base::operator*;

  explicit transform(const mat<T, 4>& m) noexcept
      : transform(m[0], m[1], m[2], m[3]) {}

  explicit transform(const mat<T, 3>& m) noexcept
      : transform(vec<T, 4>{m[0][0], m[0][1], m[0][2], 0},
                  vec<T, 4>{m[1][0], m[1][1], m[1][2], 0},
                  vec<T, 4>{m[2][0], m[2][1], m[2][2], 0},
                  vec<T, 4>{0, 0, 0, 1}) {}

  explicit transform(const vec<T, 3>& translation) noexcept;
  explicit transform(const scale<T, 3>& scale) noexcept;
  transform(const vec<T, 3>& normalizedAxis, T radian) noexcept;
  explicit transform(const quat<T>& q) noexcept;
  explicit transform(const euler<T>& e) noexcept;

  // world space -> camera space
  static const transform look_at(const point<T, 3>& pos,
                                 const point<T, 3>& target,
                                 const vec<T, 3>& up = vec<T, 3>(0, 1,
                                                                 0)) noexcept;
  // orthographic, camera space -> clip space
  static const transform orthographic(T width, T height, T zNear,
                                      T zFar) noexcept;
  // perspective, camera space -> clip space
  // fovy: vertical field of view in radian
  // aspect : width / height
  static const transform perspcetive(T fovy, T aspect, T zNear,
                                     T zFar) noexcept;

  // sample: rotate_with<Axis::X>(to_radian(theta))
  template <Axis axis>
  static const transform rotate_with(T theta) noexcept;

  inline const point<T, 3> decompose_position() const noexcept {
    return {(*this)(0, 3), (*this)(1, 3), (*this)(2, 3)};
  }

  inline const scale<T, 3> decompose_scale() const noexcept;
  inline const mat<T, 3> decompose_rotation_matrix() const noexcept;
  const quat<T> decompose_quatenion() const noexcept;
  const euler<T> decompose_euler() const noexcept;
  inline const mat<T, 3> decompose_mat3() const noexcept;

  const point<T, 3> operator*(const point<T, 3>& p) const noexcept;
  const vec<T, 3> operator*(const vec<T, 3>& v) const noexcept;
  const normal<T> operator*(const normal<T>& n) const noexcept;
};

using transformf = transform<float>;
}  // namespace My

#include "transform.inl"
