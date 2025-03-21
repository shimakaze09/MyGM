//
// Created by Admin on 26/12/2024.
//

#pragma once

#include "bbox.h"
#include "euler.h"
#include "hvec.h"
#include "line.h"
#include "mat.h"
#include "normal.h"
#include "point.h"
#include "quat.h"
#include "ray.h"
#include "scale.h"
#include "vec.h"

#include "Interfaces/IMatrix/IMatrixInOut.h"
#include "Interfaces/IMatrix/IMatrixMul.h"

namespace My {
template <typename F>
struct ImplTraits<transform<F>> : ArrayTraits<vec<F, 4>, 4, F>,
                                  IListTraits<IMatrixInOut, IMatrixMul> {};

// TODO: distinguish different kinds of transformations
// - basic transformation: translation, reflection, rotation, scaling, shearing, projection (projective transformation)
// - rigid transformation: translation + rotation + reflection
// - similarity transformation: translation + rotation + reflection + scaling
// - linear transformation: rotation + reflection + scaling + shearing
// - affine transformation: translation + linear transformation
// - transformation: affine transformation + projection
template <typename F>
struct transform : SI<transform<F>> {
  using Base = SI<transform<F>>;
  using Base::Base;
  using Base::operator*;

  inline explicit transform(const mat<F, 4>& m) noexcept;
  inline explicit transform(const mat<F, 3>& m) noexcept;

  inline explicit transform(const vec<F, 3>& translation) noexcept;
  inline explicit transform(const quat<F>& rot) noexcept;
  inline explicit transform(const euler<F>& euler) noexcept;
  inline transform(const vec<F, 3>& axis, F radian) noexcept;
  inline explicit transform(const scale<F, 3>& scale) noexcept;
  inline explicit transform(F scale) noexcept;

  inline transform(const vec<F, 3>& translation,
                   const scale<F, 3>& scale) noexcept;
  inline transform(const vec<F, 3>& translation, const quat<F>& rot) noexcept;
  inline transform(const quat<F>& rot, const scale<F, 3>& scale) noexcept;
  inline transform(const vec<F, 3>& translation, const quat<F>& rot,
                   const scale<F, 3>& scale) noexcept;

  // world space -> camera space
  // right hand, forward is camera's back
  inline static const transform look_at(
      const point<F, 3>& pos, const point<F, 3>& target,
      const vec<F, 3>& up = vec<F, 3>(0, 1, 0)) noexcept;

  // orthographic, camera space -> clip space
  inline static const transform orthographic(F width, F height, F zNear,
                                             F zFar) noexcept;
  // perspective, camera space -> clip space
  // fovy: verticle field of view in radian
  // aspect : width / height
  inline static const transform perspective(
      F fovy, F aspect, F zNear, F zFar,
      F near_clip_vlaue = MY_DEFAULT_NEAR_CLIP_VALUE) noexcept;

  // sample: rotate_with<Axis::X>(to_radian(theta))
  template <Axis axis>
  inline static const transform rotate_with(F theta) noexcept;

  inline const vec<F, 3> decompose_translation() const noexcept;
  inline const mat<F, 3> decompose_rotation_matrix() const noexcept;
  inline const quat<F> decompose_quatenion() const noexcept;
  inline const euler<F> decompose_euler() const noexcept;
  inline const mat<F, 3> decompose_mat3() const noexcept;
  inline const scale<F, 3> decompose_scale() const noexcept;

  // faster than IMatrixMul::inverse
  // "sim" : similarity (translation, scaling, rotation [reflection])
  // ref: https://en.wikipedia.org/wiki/Similarity_(geometry)
  inline const transform inverse_sim() const noexcept;
  // TODO: transform::inverse_rigid
  // const transform inverse_rigid() const noexcept;

  inline const hvec<F, 4> operator*(const hvec<F, 4>& hv) const noexcept;
  inline const point<F, 3> operator*(const point<F, 3>& p) const noexcept;
  inline const vec<F, 3> operator*(const vec<F, 3>& v) const noexcept;
  // result isn't normalized
  inline const normal<F> operator*(const normal<F>& n) const noexcept;
  inline const bbox<F, 3> operator*(const bbox<F, 3>& b) const noexcept;
  inline const line<F, 3> operator*(const line<F, 3>& r) const noexcept;
  inline const ray<F, 3> operator*(const ray<F, 3>& r) const noexcept;
};

using transformf = transform<float>;

// maybe error in editor, but no compile error
static_assert(sizeof(transformf) == 16 * sizeof(float));
}  // namespace My

#include "details/transform.inl"
