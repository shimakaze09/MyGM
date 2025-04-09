#pragma once

#include "IAdd.h"
#include "IScalarMul.h"

#include <MyTemplate/SI.h>

namespace My {
template <typename Base, typename Impl>
struct ILinear;
}

SI_CombineInterface(My::ILinear, My::IAdd, My::IScalarMul);
