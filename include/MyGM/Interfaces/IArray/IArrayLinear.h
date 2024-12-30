//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "../ILinear.h"
#include "IArrayAdd.h"
#include "IArrayScalarMul.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IArrayLinear
    : SIVT_CRTP<TemplateList<IArrayAdd, IArrayScalarMul, ILinear>, Base, Impl,
                ArgList> {
  using SIVT_CRTP<TemplateList<IArrayAdd, IArrayScalarMul, ILinear>, Base, Impl,
                  ArgList>::SIVT_CRTP;
};
}  // namespace My