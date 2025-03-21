//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "svec.h"
#include "val.h"

namespace My {
// [0, 1) x [0, 1)
template <typename T>
inline const val<T, 2> uniform_in_square() noexcept;

// center: (0, 0), radius: 1
template <typename T>
inline const val<T, 2> uniform_on_disk() noexcept;

// center: (0, 0), radius: [0, 1)
template <typename T>
inline const val<T, 2> uniform_in_disk() noexcept;

// center: (0, 0, 0), radius: 1
template <typename T>
inline const val<T, 3> uniform_on_sphere() noexcept;

// center: (0, 0, 0), radius: [0, 1)
template <typename T>
inline const val<T, 3> uniform_in_sphere() noexcept;

// center: (0, 0, 0), radius: 1
template <typename T, Axis up = Axis::Z>
inline const val<T, 3> cos_weighted_on_hemisphere() noexcept;

// [summary]
// sample microfacet normal from GGX normal distribuion function
// ref: Walter B, et al. Microfacet Models for Refraction through Rough Surfaces.
// [return]
// wm: microfacet normal
inline const svecf sample_GGX_D(float alpha) noexcept;
}  // namespace My

#include "details/sample.inl"