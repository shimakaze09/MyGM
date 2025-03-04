//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "IAdd.h"
#include "IScalarMul.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct ILinear : Base {
  using IList = TemplateList<IAdd, IScalarMul>;
  using Base::Base;
};
}  // namespace My