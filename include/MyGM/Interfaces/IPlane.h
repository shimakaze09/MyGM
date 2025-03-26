#pragma once

#include "IAffineRealSubspace.h"
#include "IOPlane.h"

namespace My {
// plane in real affine subspace
CombineInterface(IPlane, IAffineRealSubspace, IOPlane);
}  // namespace My
