#pragma once

#include <MyTemplate/SI.hpp>

#include "IAdd.hpp"
#include "IScalarMul.hpp"

namespace My {
template <typename Base, typename Impl>
struct ILinear;
}

SI_CombineInterface(My::ILinear, My::IAdd, My::IScalarMul);
