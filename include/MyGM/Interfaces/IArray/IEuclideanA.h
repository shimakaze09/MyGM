#pragma once

#include "IEuclideanV.h"

#include "../IAffine.h"
#include "../IMetric.h"

namespace My {
// euclidean affine space
template <typename Base, typename Point>
struct IEuclideanA : Base {
  using Base::Base;

  using T = ImplTraits_T<Point>;
  static constexpr size_t N = ImplTraits_N<Point>;
  using F = ImplTraits_F<Point>;
  using Vector = ImplTraits_V<Point>;

  static_assert(SI_Contains_v<Vector, ILinear>);
  static_assert(ImplTraits_N<Vector> == N);

  static F distance2(const Point& x, const Point& y) noexcept {
    return (x - y).norm2();
  }

  F distance2(const Point& y) const noexcept {
    auto& x = static_cast<const Point&>(*this);
    return distance2(x, y);
  }

 private:
  template <typename Base, typename Impl>
  friend struct IAffineSubspace;

  Point impl_affine_subspace_add(const Vector& v) const noexcept {
    auto& p = static_cast<const Point&>(*this);
#ifdef MY_USE_SIMD
    if constexpr (ImplTraits_SupportSIMD<Point>)
      return _mm_add_ps(p, v);
    else
#endif  // MY_USE_SIMD
    {
      Point rst;
      for (size_t i = 0; i < N; i++)
        rst[i] = p[i] + v[i];
      return rst;
    }
  }

  Point& impl_affine_subspace_add_to_self(const Vector& v) noexcept {
    auto& p = static_cast<Point&>(*this);
#ifdef MY_USE_SIMD
    if constexpr (ImplTraits_SupportSIMD<Point>)
      return p = p + v;
    else
#endif  // MY_USE_SIMD
      for (size_t i = 0; i < N; i++)
        p[i] += v[i];
    return p;
  }

  Point impl_affine_subspace_minus(const Vector& v) const noexcept {
    auto& p = static_cast<const Point&>(*this);
#ifdef MY_USE_SIMD
    if constexpr (ImplTraits_SupportSIMD<Point>)
      return _mm_sub_ps(p, v);
    else
#endif  // MY_USE_SIMD
    {
      Point rst;
      for (size_t i = 0; i < N; i++)
        rst[i] = p[i] - v[i];
      return rst;
    }
  }

  Point& impl_affine_subspace_minus_to_self(const Vector& v) noexcept {
    auto& p = static_cast<Point&>(*this);
#ifdef MY_USE_SIMD
    if constexpr (ImplTraits_SupportSIMD<Point>)
      return p = p - v;
    else
#endif  // MY_USE_SIMD
      for (size_t i = 0; i < N; i++)
        p[i] -= v[i];
    return p;
  }

  template <typename Base, typename Impl>
  friend struct IAffine;

  const Vector impl_affine_minus(const Point& y) const noexcept {
    auto& x = static_cast<const Point&>(*this);
#ifdef MY_USE_SIMD
    if constexpr (ImplTraits_SupportSIMD<Point>)
      return _mm_sub_ps(x, y);
    /* // no benefits
			else if constexpr (std::is_same_v<T, float> && N == 3) {
				Vector rst;
				auto sx = _mm_loadu_ps(x.data());
				auto sy = _mm_loadu_ps(y.data());
				auto srst = sx - sy;
				return { srst[0], srst[1],srst[2] };
			}*/
    else
#endif  // MY_USE_SIMD
    {
      Vector rst;
      for (size_t i = 0; i < N; i++)
        rst[i] = x[i] - y[i];
      return rst;
    }
  }

  template <typename Base, typename Impl>
  friend struct IMetric;

  static F impl_distance(const Point& x, const Point& y) noexcept {
    return std::sqrt(distance2(x, y));
  }
};

InterfaceTraits_Register(IEuclideanA, IMetric, IAffine, IArray);
}  // namespace My
