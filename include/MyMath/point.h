//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "Interfaces/IArray/IArrayInOut.h"
#include "Interfaces/IArray/IEuclideanA.h"
#include "vec.h"

namespace My {
template <typename T, size_t N>
struct point : SIIT_CRTP<TemplateList<IArrayInOut, IEuclideanA>, point<T, N>,
                         TypeList<TypeList<T, Size<N>>, T, vec<T, N>>> {
  using SIIT_CRTP<TemplateList<IArrayInOut, IEuclideanA>, point<T, N>,
                  TypeList<TypeList<T, Size<N>>, T, vec<T, N>>>::SIIT_CRTP;

  explicit point(const vec<T, N>& vec) {
    for (size_t i = 0; i < N; i++)
      (*this)[i] = vec[i];
  }
};

template <size_t N>
using pointf = point<float, N>;

using pointf1 = pointf<1>;
using pointf2 = pointf<2>;
using pointf3 = pointf<3>;
using pointf4 = pointf<4>;
}  // namespace My