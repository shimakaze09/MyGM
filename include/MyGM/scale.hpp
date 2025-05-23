#pragma once

#include "Interfaces/IArray/IArray1D_Util.hpp"
#include "Interfaces/IArray/IArrayHadamardProduct.hpp"
#include "Interfaces/IArray/IArrayScalarMul.hpp"
#include "details/traits.hpp"

namespace Smkz {
template <typename T, size_t N>
struct SI_ImplTraits<scale<T, N>>
    : Array1DTraits<T, N>,
      IListTraits<IArray1D_Util, IArrayHadamardProduct, IArrayScalarMul>,
      ArrayImplNTraits<scale, T> {};

template <typename T, size_t N>
struct scale : SI<scale<T, N>> {
  using SI<scale<T, N>>::SI;
};

template <size_t N>
using scalef = scale<float, N>;

using scalef1 = scalef<1>;
using scalef2 = scalef<2>;
using scalef3 = scalef<3>;
using scalef4 = scalef<4>;

// maybe error in editor, but no compile error
static_assert(sizeof(scalef4) == 4 * sizeof(float));
}  // namespace  Smkz
