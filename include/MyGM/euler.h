//
// Created by Admin on 26/12/2024.
//

#pragma once

#include "Interfaces/IArray/IArray1D_Util.h"

namespace My {
template <typename T>
struct quat;

// same with Unity3D
// Z -> X -> Y
// roll -> pitch -> yaw
// Tait CBryan angles, extrinsic rotations (math: x-y-z, game: z-x-y)
// ref: https://en.wikipedia.org/wiki/Euler_angles
template <typename T>
struct euler : SIIT_CRTP<TemplateList<IArray1D_Util>, euler<T>,
                         TypeList<TypeList<T, Size<3>>, T>> {
  using SIIT_CRTP<TemplateList<IArray1D_Util>, euler<T>,
                  TypeList<TypeList<T, Size<3>>, T>>::SIIT_CRTP;

  const quat<T> to_quat() const noexcept;
};

using eulerf = euler<float>;

// maybe error in editor, but no compile error
static_assert(sizeof(eulerf) == 3 * sizeof(float));
}  // namespace My

#include "detail/euler.inl"