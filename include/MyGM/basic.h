//
// Created by Admin on 26/12/2024.
//

#pragma once

#include "config.h"

#include <cmath>
#include <random>

namespace My {
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto EPSILON = static_cast<T>(0.001);

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto PI = static_cast<T>(3.141592653589793);

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto ZERO = static_cast<T>(0);

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto ONE = static_cast<T>(1);

enum class Axis : uint8_t {
  X = 0,
  Y = 1,
  Z = 2,
  INVALID = 3,
};

template <typename T>
inline const T rmv_epsilon(T val) noexcept;

template <typename T>
inline constexpr T to_radian(T degree) noexcept;

template<typename T>
inline constexpr T to_degree(T radian) noexcept;

template <typename T>
inline T sgn(T v) noexcept;

template <typename T>
inline bool is_zero(T v) noexcept;

template <typename T>
inline bool is_nan(T v) noexcept;

template <typename T, typename F>
inline T lerp(T x, T y, F t) noexcept;

// 1 - epsilon, T: float / double
template <typename T>
inline constexpr T one_epsilon() noexcept;

// range: [0, 1), T: float / double
template <typename T>
inline T rand01() noexcept;

// range: [0, 2^64-1]
inline size_t randi() noexcept;

template <typename T>
inline constexpr T pow2(T x) noexcept;
template <typename T>
inline constexpr T pow5(T x) noexcept;
}  // namespace My

#include "details/basic.inl"
