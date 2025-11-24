#pragma once

#include "Interfaces/IArray/IArray1D_Util.hpp"
#include "Interfaces/IArray/ICross.hpp"
#include "details/traits.hpp"

namespace My {
/**
 * @brief Traits for the vec class.
 *
 * Defines the properties of the vec class, including its element type,
 * dimension, and the interfaces it implements.
 *
 * @tparam T The element type (e.g., float, int).
 * @tparam N The dimension of the vector.
 */
template <typename T, size_t N>
struct SI_ImplTraits<vec<T, N>> : Array1DTraits<T, N>,
                                  IListTraits<IArray1D_Util, IEuclideanV>,
                                  ArrayImplNTraits<vec, T>,
                                  SIMDTraits<true> {};

/**
 * @brief Specialization of traits for 3D vectors.
 *
 * Adds the ICross interface for 3D vectors to support cross product operations.
 */
template <typename T>
struct SI_ImplTraits<vec<T, 3>> : Array1DTraits<T, 3>,
                                  IListTraits<IArray1D_Util, ICross>,
                                  ArrayImplNTraits<vec, T> {};

/**
 * @brief A generic vector class.
 *
 * Represents a mathematical vector with N components of type T.
 * It inherits functionality from various interfaces via the SI (Static Interface)
 * base class.
 *
 * @tparam T The element type.
 * @tparam N The dimension.
 */
template <typename T, size_t N>
struct vec : SI<vec<T, N>> {
  using SI<vec<T, N>>::SI;
};

template <size_t N>
using vecf = vec<float, N>;

using vecf1 = vecf<1>;
using vecf2 = vecf<2>;
using vecf3 = vecf<3>;
using vecf4 = vecf<4>;

template <size_t N>
using veci = vec<int, N>;

using veci1 = veci<1>;
using veci2 = veci<2>;
using veci3 = veci<3>;
using veci4 = veci<4>;

template <size_t N>
using vecu = vec<unsigned, N>;

using vecu1 = vecu<1>;
using vecu2 = vecu<2>;
using vecu3 = vecu<3>;
using vecu4 = vecu<4>;

// maybe error in editor, but no compile error
static_assert(sizeof(vecf4) == 4 * sizeof(float));
}  // namespace My
