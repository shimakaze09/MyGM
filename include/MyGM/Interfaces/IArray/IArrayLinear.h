//
// Created by Admin on 30/12/2024.
//

#pragma once

#include "../ILinear.h"
#include "IArrayAdd.h"
#include "IArrayScalarMul.h"

namespace My {
CombineInterface(IArrayLinear, IArrayAdd, IArrayScalarMul, ILinear);
}  // namespace My