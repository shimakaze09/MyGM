//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "IInnerProduct.h"
#include "ILinear.h"

namespace My {
template <typename Base, typename Impl, typename T, typename N>
struct IEuclidean
    : SIVT_CRTP<TemplateList<IInnerProduct, ILinear>, Base, Impl, T, N> {
  using SIVT_CRTP<TemplateList<IInnerProduct, ILinear>, Base, Impl, T,
                  N>::SIVT_CRTP;
};
}  // namespace My
