#pragma once

#include "IAdd.h"
#include "IScalarMul.h"

#include <MyTemplate/SI.h>

namespace My {
SI_CombineInterface(ILinear, IAdd, IScalarMul);
}  // namespace My
