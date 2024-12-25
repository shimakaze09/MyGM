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
struct rgb : SIIT_CRTP<TemplateList<IArrayInOut, IArrayHadamardProduct, ILinear,
                                    IArrayScalarMul, IArrayAdd>,
                       rgb<T>, TypeList<TypeList<T, Size<3>>, T>> {
  using SIIT_CRTP<TemplateList<IArrayInOut, IArrayHadamardProduct, ILinear,
                               IArrayScalarMul, IArrayAdd>,
                  rgb<T>, TypeList<TypeList<T, Size<3>>, T>>::SIIT_CRTP;
};

using rgbf = rgb<float>;
}  // namespace My