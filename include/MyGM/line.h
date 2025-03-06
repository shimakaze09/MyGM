//
// Created by Admin on 29/12/2024.
//

#pragma once

#include "basic.h"
#include "bbox.h"
#include "triangle.h"

#include "Interfaces/ILine.h"

namespace My {
template <typename T, size_t N>
struct line;

template <typename T, size_t N_>
struct ImplTraits<line<T, N_>> {
  using IList = TemplateList<IInOut, ILine>;
  using V = vec<T, N_>;
  using P = point<T, N_>;
  static constexpr size_t N = N_;
  using F = T;
};

template <typename T, size_t N>
struct line : SI<line<T, N>> {
  using SI<line<T, N>>::SI;

  inline line(const point<T, N>& p, const vec<T, N>& dir) noexcept {
    this->init_ILine(p, dir);
  }

  inline void print(std::ostream& os = std::cout) const;

  // (isIntersect, (w, u, v), t)
  MY_FORCEINLINE const std::tuple<bool, std::array<T, 3>, T> intersect(
      const triangle<T, 3>& tri) const noexcept;
  // (isIntersect, t0, t1)
  inline const std::tuple<bool, T, T> intersect(
      const bbox<T, N>& box, T tmin = std::numeric_limits<T>::max(),
      T tmax = std::numeric_limits<T>::min()) const noexcept;
  inline const std::tuple<bool, T, T> intersect(
      const bbox<T, N>& box, const vec<T, N>& inv_dir,
      T tmin = std::numeric_limits<T>::max(),
      T tmax = std::numeric_limits<T>::min()) const noexcept;

 private:
  template <typename Base, typename Impl>
  friend struct IInOut;

  inline std::ostream& impl_out(std::ostream& os) const;
  inline std::istream& impl_in(std::istream& is);

  template <typename Base, typename Impl>
  friend struct IAffineRealSubspace;

  inline static const line impl_move(const line& line,
                                     const point<T, N>& p) noexcept;
};

template <size_t N>
using linef = line<float, N>;

using linef1 = linef<1>;
using linef2 = linef<2>;
using linef3 = linef<3>;

// maybe error in editor, but no compile error
static_assert(sizeof(linef3) == 6 * sizeof(float));
}  // namespace My

#include "detail/line.inl"
