#pragma once

#include "IAffineRealSubspace.hpp"
#include "IOPlane.hpp"

namespace My {
template <typename Base, typename Impl>
struct IPlane;
}

// plane in real affine subspace
SI_CombineInterface(My::IPlane, My::IAffineRealSubspace, My::IOPlane);
