//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "IAdd.h"
#include "IMul.h"

#include <MyTemplate/SI.h>

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IRing : SIVT_CRTP<TemplateList<IMul, IAdd>, Base, Impl, ArgList> {
  using SIVT_CRTP<TemplateList<IMul, IAdd>, Base, Impl, ArgList>::SIVT_CRTP;
};
}  // namespace My
