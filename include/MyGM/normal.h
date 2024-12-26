//
// Created by Admin on 26/12/2024.
//

#pragma once

#include "Interfaces/IArray/IArray1D_Util.h"
#include "Interfaces/IArray/IArrayInOut.h"
#include "Interfaces/IArray/IEuclideanV.h"

namespace My {
template <typename T, size_t N>
struct vec;

template <typename T>
struct normal : SIIT_CRTP<TemplateList<IArray1D_Util, IArrayInOut, IEuclideanV>,
                          normal<T>, TypeList<TypeList<T, Size<3>>, T>> {
  using SIIT_CRTP<TemplateList<IArray1D_Util, IArrayInOut, IEuclideanV>,
                  normal<T>, TypeList<TypeList<T, Size<3>>, T>>::SIIT_CRTP;

  inline explicit normal(const vec<T, 3>& v) {
    for (size_t i = 0; i < 3; i++)
      (*this)[i] = v[i];
  }

  inline static const normal cross(const normal& x, const normal& y) noexcept {
    return normal{x[1] * y[2] - x[2] * y[1], x[2] * y[0] - x[0] * y[2],
                  x[0] * y[1] - x[1] * y[0]};
  }

  inline const normal cross(const normal& y) const noexcept {
    const normal& x = *this;
    return cross(x, y);
  }

  inline static T sin_theta(const normal& x, const normal& y) noexcept {
    T xN = x.norm();
    T yN = y.norm();
    T xyN = xN * yN;
    assert(xyN > 0);
    return cross(x, y) / xyN;
  }

  inline T sin_theta(const normal& y) const noexcept {
    const normal& x = *this;
    return sin_theta(x, y);
  }
};

using normalf = normal<float>;
}  // namespace My
