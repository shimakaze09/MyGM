//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "vec.h"

#include "Interfaces/IArray/IArray1D_Util.h"
#include "Interfaces/IArray/IArrayUtil.h"
#include "Interfaces/IArray/IEuclideanA.h"

namespace My {
template <typename T, size_t N>
struct vec;

template <typename T, size_t N>
struct val;

template <typename T, size_t N>
struct point : SIIT_CRTP<TemplateList<IArrayUtil, IEuclideanA>, point<T, N>,
                         TypeList<TypeList<T, Size<N>>, T, vec<T, N>>> {
  using SIIT_CRTP<TemplateList<IArrayUtil, IEuclideanA>, point<T, N>,
                  TypeList<TypeList<T, Size<N>>, T, vec<T, N>>>::SIIT_CRTP;
};

template <size_t N>
using pointf = point<float, N>;

using pointf1 = pointf<1>;
using pointf2 = pointf<2>;
using pointf3 = pointf<3>;
using pointf4 = pointf<4>;
}  // namespace My