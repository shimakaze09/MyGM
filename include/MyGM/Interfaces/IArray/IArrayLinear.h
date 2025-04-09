#pragma once

#include "../ILinear.h"
#include "IArrayAdd.h"
#include "IArrayScalarMul.h"

namespace My {
template <typename Base, typename Impl>
struct IArrayLinear;
}  // namespace My

SI_CombineInterface(My::IArrayLinear, My::IArrayAdd, My::IArrayScalarMul,
                    My::ILinear);
