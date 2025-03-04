//
// Created by Admin on 26/12/2024.
//

#pragma once

#include "IArray.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IArray1D : Base {
  using IList = TemplateList<IArray>;
  using Base::Base;
  static_assert(std::is_same_v<Arg_T<ArgList>, Arg_F<ArgList>>);
};
}  // namespace My
