//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "../ILinear.h"
#include "IArrayAdd.h"
#include "IArrayScalarMul.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IArrayLinear : Base {
  using IList = TemplateList<IArrayAdd, IArrayScalarMul, ILinear>;
  using Base::Base;
};
}  // namespace My