//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../IInnerProduct.h"
#include "../ILinear.h"
#include "../INorm.h"
#include "IArrayAdd.h"
#include "IArrayScalarMul.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IEuclidean : SIVT_CRTP<TemplateList<INorm, IInnerProduct, ILinear,
                                           IArrayScalarMul, IArrayAdd>,
                              Base, Impl, ArgList> {
  using T = At_t<ArgList, 0>;
  using N = At_t<ArgList, 1>;

  using SIVT_CRTP<
      TemplateList<INorm, IInnerProduct, ILinear, IArrayScalarMul, IArrayAdd>,
      Base, Impl, ArgList>::SIVT_CRTP;

 private:
  template <typename Base, typename Impl, typename ArgList>
  friend struct IInnerProduct;

  static T impl_dot(const Impl& x, const Impl& y) noexcept {
    T rst = x[0] * y[0];
    for (size_t i = 1; i < N::value; i++)
      rst += x[i] * y[i];
    return rst;
  }
};
}  // namespace My
