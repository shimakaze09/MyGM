#pragma once

#include "Interfaces/IArray/IArray1D_Util.hpp"
#include "quat.hpp"

namespace Smkz {
template <typename T>
struct SI_ImplTraits<euler<T>> : Array1DTraits<T, 3>,
                                 IListTraits<IArray1D_Util> {};

// same with Unity3D
// Z -> X -> Y
// roll -> pitch -> yaw
// Tait�CBryan angles, extrinsic rotations (math: x-y-z, game: z-x-y)
// ref: https://en.wikipedia.org/wiki/Euler_angles
// degree
template <typename T>
struct euler : SI<euler<T>> {
  using SI<euler<T>>::SI;

  quat<T> to_quat() const noexcept;
};

using eulerf = euler<float>;

// maybe error in editor, but no compile error
static_assert(sizeof(eulerf) == 3 * sizeof(float));
}  // namespace  Smkz

#include "details/euler.inl"
