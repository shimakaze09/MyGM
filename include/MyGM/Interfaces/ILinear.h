//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "IAdd.h"
#include "IScalarMul.h"

#include <MyTemplate/SI.h>

namespace My {
CombineInterface(ILinear, IAdd, IScalarMul);
}  // namespace My