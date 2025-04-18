#pragma once

#include <MyTemplate/SI.hpp>

#include "IAdd.hpp"
#include "IScalarMul.hpp"

namespace Smkz {
template <typename Base, typename Impl>
struct ILinear;
}

SI_CombineInterface(Smkz::ILinear, Smkz::IAdd, Smkz::IScalarMul);
