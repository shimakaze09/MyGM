#pragma once

#include "IAffineRealSubspace.h"
#include "IOPlane.h"

namespace My {
template <typename Base, typename Impl>
struct IPlane;
}  // namespace My

// plane in real affine subspace
SI_CombineInterface(My::IPlane, My::IAffineRealSubspace, My::IOPlane);
