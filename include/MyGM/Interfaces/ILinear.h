#pragma once

#include "IAdd.h"
#include "IScalarMul.h"

#include <MyTemplate/SI.h>

namespace My {
template <typename Base, typename Impl>
struct ILinear;
}  // namespace My

SI_CombineInterface(ILinear, IAdd, IScalarMul);
