//
// Created by Admin on 27/12/2024.
//

#pragma once

#include "IArrayCast.h"
#include "IArrayInOut.h"

namespace My {
template<typename Base, typename Impl, typename ArgList>
struct IArrayUtil : SIVT_CRTP<TemplateList<IArrayCast, IArrayInOut>, Base, Impl, ArgList> {
  using SIVT_CRTP<TemplateList<IArrayCast, IArrayInOut>, Base, Impl, ArgList>::SIVT_CRTP;
};
}
