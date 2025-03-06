//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "IAdd.h"
#include "IMul.h"

#include <MyTemplate/SI.h>

namespace My {
CombineInterface(IRing, IAdd, IMul);
}  // namespace My
