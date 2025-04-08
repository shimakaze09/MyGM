#pragma once

#include "../ILinear.h"
#include "IArrayAdd.h"
#include "IArrayScalarMul.h"

namespace My {
SI_CombineInterface(IArrayLinear, IArrayAdd, IArrayScalarMul, ILinear);
}  // namespace My
