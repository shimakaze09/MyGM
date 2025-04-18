#pragma once

#include "../ILinear.hpp"
#include "IArrayAdd.hpp"
#include "IArrayScalarMul.hpp"

namespace My {
template <typename Base, typename Impl>
struct IArrayLinear;
}

SI_CombineInterface(My::IArrayLinear, My::IArrayAdd, My::IArrayScalarMul,
                    My::ILinear);
