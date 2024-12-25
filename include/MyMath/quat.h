//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "Interfaces/IQuat/IQuatInOut.h"
#include "Interfaces/IQuat/IQuatMul.h"
#include "point.h"
#include "vec.h"

namespace My {
template <typename T>
struct quat : SIIT_CRTP<TemplateList<IQuatInOut, IQuatMul>, quat<T>, T> {
  using SIIT_CRTP<TemplateList<IQuatInOut, IQuatMul>, quat<T>, T>::SIIT_CRTP;
};

using quatf = quat<float>;
}  // namespace My
