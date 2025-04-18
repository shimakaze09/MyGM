#pragma once

#include "../ILinear.hpp"
#include "IArrayAdd.hpp"
#include "IArrayScalarMul.hpp"

namespace Smkz {
template <typename Base, typename Impl>
struct IArrayLinear;
}

SI_CombineInterface(Smkz::IArrayLinear, Smkz::IArrayAdd, Smkz::IArrayScalarMul,
                    Smkz::ILinear);
