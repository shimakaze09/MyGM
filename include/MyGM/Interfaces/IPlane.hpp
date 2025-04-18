#pragma once

#include "IAffineRealSubspace.hpp"
#include "IOPlane.hpp"

namespace Smkz {
template <typename Base, typename Impl>
struct IPlane;
}

// plane in real affine subspace
SI_CombineInterface(Smkz::IPlane, Smkz::IAffineRealSubspace, Smkz::IOPlane);
