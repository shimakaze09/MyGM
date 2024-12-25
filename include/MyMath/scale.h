//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "Interfaces/IArray/IArrayAdd.h"
#include "Interfaces/IArray/IArrayHadamardProduct.h"
#include "Interfaces/IArray/IArrayInOut.h"
#include "Interfaces/IArray/IArrayScalarMul.h"
#include "Interfaces/ILinear.h"

namespace My {
template <typename T>
struct scale : SIIT_CRTP<TemplateList<IArrayInOut, IArrayHadamardProduct,
                                      ILinear, IArrayScalarMul, IArrayAdd>,
                         scale<T>, TypeList<TypeList<T, Size<3>>, T>> {
  using SIIT_CRTP<TemplateList<IArrayInOut, IArrayHadamardProduct, ILinear,
                               IArrayScalarMul, IArrayAdd>,
                  scale<T>, TypeList<TypeList<T, Size<3>>, T>>::SIIT_CRTP;
};

using scalef = scale<float>;
}  // namespace My
