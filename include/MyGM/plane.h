//
// Created by Admin on 29/12/2024.
//

#pragma once

#include "point.h"
#include "vec.h"

#include "Interfaces/IPlane.h"

namespace My {
template <typename T>
struct plane;

template <typename T>
struct ImplTraits<plane<T>> {
  using IList = TemplateList<IInOut, IPlane>;
  using V = vec<T, 3>;
  using P = point<T, 3>;
  using F = T;
};

template <typename T>
struct plane : SI<plane<T>> {
  using SI<plane<T>>::SI;

  plane(const point<T, 3>& p, const vec<T, 3>& n) noexcept {
    this->init_IPlane(p, n);
  }

  inline void print(std::ostream& os = std::cout) const;

 private:
  template <typename Base, typename Impl>
  friend struct IInOut;
  inline std::ostream& impl_out(std::ostream& os) const;
  inline std::istream& impl_in(std::istream& is);
};

using planef = plane<float>;

// maybe error in editor, but no compile error
static_assert(sizeof(planef) == 6 * sizeof(float));
}  // namespace My

#include "detail/plane.inl"