#pragma once

#include "svec.h"
#include "val.h"

namespace My {
// [0, 1) x [0, 1)
template <typename T>
val<T, 2> uniform_in_square() noexcept;

// center: (0, 0), radius: 1
template <typename T>
val<T, 2> uniform_on_disk() noexcept;

// center: (0, 0), radius: [0, 1)
template <typename T>
val<T, 2> uniform_in_disk() noexcept;

// center: (0, 0, 0), radius: 1
template <typename T>
val<T, 3> uniform_on_sphere() noexcept;

// center: (0, 0, 0), radius: [0, 1)
template <typename T>
val<T, 3> uniform_in_sphere() noexcept;

// center: (0, 0, 0), radius: 1
template <typename T, Axis up = Axis::Z>
val<T, 3> cos_weighted_on_hemisphere() noexcept;

// [summary]
// sample micro facet normal from GGX normal distribution function
// ref: Walter B, et al. Micro facet Models for Refraction through Rough Surfaces.
// [return]
// wm: micro facet normal
svecf sample_GGX_D(float alpha) noexcept;
}  // namespace My

#include "details/sample.inl"
