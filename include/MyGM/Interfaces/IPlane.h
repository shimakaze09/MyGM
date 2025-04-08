#pragma once

#include "IAffineRealSubspace.h"
#include "IOPlane.h"

namespace My {
// plane in real affine subspace
SI_CombineInterface(IPlane, IAffineRealSubspace, IOPlane);
}  // namespace My
