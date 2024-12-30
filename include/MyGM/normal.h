//
// Created by Admin on 26/12/2024.
//

#pragma once

#include "Interfaces/IArray/IArray1D_Util.h"
#include "Interfaces/IArray/ICross.h"

namespace My {
template <typename T>
struct normal : SIIT_CRTP<TemplateList<IArray1D_Util, ICross>, normal<T>,
                          TypeList<TypeList<T, Size<3>>, T>> {
  using SIIT_CRTP<TemplateList<IArray1D_Util, ICross>, normal<T>,
                  TypeList<TypeList<T, Size<3>>, T>>::SIIT_CRTP;
};

using normalf = normal<float>;
}  // namespace My