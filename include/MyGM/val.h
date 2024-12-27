//
// Created by Admin on 25/12/2024.
//

#pragma once

#include <MyTemplate/SI.h>
#include "Interfaces/IArray/IArray1D_Util.h"
#include "Interfaces/IArray/IArrayUtil.h"

namespace My {
template <typename T, size_t N>
struct val : SIIT_CRTP<TemplateList<IArray1D_Util, IArrayUtil>, val<T, N>,
                       TypeList<TypeList<T, Size<N>>, T>> {
  using SIIT_CRTP<TemplateList<IArray1D_Util, IArrayUtil>, val<T, N>,
                  TypeList<TypeList<T, Size<N>>, T>>::SIIT_CRTP;
};

template <size_t N>
using valf = val<float, N>;

using valf1 = valf<1>;
using valf2 = valf<2>;
using valf3 = valf<3>;

template <size_t N>
using vali = val<int, N>;

using vali1 = vali<1>;
using vali2 = vali<2>;
using vali3 = vali<3>;

template <size_t N>
using valu = val<unsigned, N>;

using valu1 = valu<1>;
using valu2 = valu<2>;
using valu3 = valu<3>;
}  // namespace My
