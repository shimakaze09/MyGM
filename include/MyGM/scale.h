//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "Interfaces/IArray/IArray1D_Util.h"
#include "Interfaces/IArray/IArrayHadamardProduct.h"
#include "Interfaces/IArray/IArrayScalarMul.h"

namespace My {
template <typename T, size_t N>
struct scale
    : SIIT_CRTP<
          TemplateList<IArray1D_Util, IArrayHadamardProduct, IArrayScalarMul>,
          scale<T, N>, TypeList<TypeList<T, Size<N>>, T>> {
  using SIIT_CRTP<
      TemplateList<IArray1D_Util, IArrayHadamardProduct, IArrayScalarMul>,
      scale<T, N>, TypeList<TypeList<T, Size<N>>, T>>::SIIT_CRTP;
};

template <size_t N>
using scalef = scale<float, N>;

using scalef1 = scalef<1>;
using scalef2 = scalef<2>;
using scalef3 = scalef<3>;
using scalef4 = scalef<4>;

// maybe error in editor, but no compile error
static_assert(sizeof(scalef4) == 4 * sizeof(float));
}  // namespace My
