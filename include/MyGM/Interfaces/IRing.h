//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "IAdd.h"
#include "IMul.h"

#include <MyTemplate/SI.h>

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IRing : Base {
  using IList = TemplateList<IMul, IAdd>;
  using Base::Base;
};
}  // namespace My
