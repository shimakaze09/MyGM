//
// Created by Admin on 27/12/2024.
//

#pragma once

#include "rgb.h"

#include "Interfaces/IArray/IArray1D_Util.h"

namespace My {
template <typename T>
struct rgba : SIIT_CRTP<TemplateList<IArray1D_Util>, rgba<T>,
                        TypeList<TypeList<T, Size<4>>, T>> {
  using Base = SIIT_CRTP<TemplateList<IArray1D_Util>, rgba<T>,
                         TypeList<TypeList<T, Size<4>>, T>>;
  using Base::Base;

  rgba(const rgb<T>& rgb, T a) noexcept : Base{rgb[0], rgb[1], rgb[2], a} {}

  explicit rgba(const rgb<T>& rgb) noexcept : rgba(rgb, ONE<T>) {}

 public:
  const rgb<T> to_rgb() const noexcept {
    return rgb<T>((*this)[0], (*this)[1], (*this)[2]) * (*this)[3];
  }

  const rgb<T> over(const rgb<T>& rgb) const noexcept {
    return to_rgb() + rgb * (ONE<T> - (*this)[3]);
  }

  const rgba over(const rgba& c) const noexcept {
    // rstA = 1 - (1-a)(1-c[3])
    T a = (*this)[3];
    const auto rstA = a + c[3] - a * c[3];
    if (rstA == ZERO<T>)
      return rgba(0, 0, 0, 0);

    const auto rstRGB = (to_rgb() + c.to_rgb() * a) / rstA;
    return rgba(rstRGB, rstA);
  }
};

using rgbaf = rgba<float>;

// maybe error in editor, but no compile error
static_assert(sizeof(rgbaf) == 4 * sizeof(float));
}  // namespace My
