//
// Created by Admin on 25/12/2024.
//

#pragma once

#include "../IAffine.h"
#include "../IMetric.h"
#include "IEuclideanV.h"

#include <vector>

namespace My {
// euclidean affine space
template <typename Base, typename Impl, typename ArgList>
struct IEuclideanA
    : SIVT_CRTP<TemplateList<IMetric, IAffine>, Base, Impl, ArgList> {
  using ImplV = Arg_ImplV<ArgList>;
  using ImplP = Arg_ImplP<ArgList>;
  using F = Arg_F<ArgList>;
  static constexpr size_t N = ImplV::N;

  static_assert(ExistInstance_v<typename ImplV::AllVBs, IEuclideanV>);

  using SIVT_CRTP<TemplateList<IMetric, IAffine>, Base, Impl,
                  ArgList>::SIVT_CRTP;

  ImplP& get_point() noexcept {
    static_assert(ImplP::N == N);
    return static_cast<Impl*>(this)->impl_get_point();
  }

  const ImplP& get_point() const noexcept {
    return const_cast<IEuclideanA*>(this)->get_point();
  }

  static const Impl move(const Impl& impl, const ImplP& p) noexcept {
    return Impl::impl_move(impl, p);
  }

  const Impl move(const ImplP& p) const noexcept {
    auto& impl = static_cast<const Impl&>(*this);
    return move(impl, p);
  }

  Impl& move_self(const ImplP& p) noexcept {
    get_point() = p;
    return static_cast<Impl&>(*this);
  }

  inline static F distance2(const Impl& x, const Impl& y) noexcept {
    return (x - y).norm2();
  }

  inline F distance2(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    return distance2(x, y);
  }

 private:
  template <typename Base, typename Impl, typename ArgList>
  friend struct IAffine;

  inline const Impl impl_affine_add(const ImplV& v) const noexcept {
    auto& impl = static_cast<const Impl&>(*this);
    auto& p = impl.get_point();
    ImplP movedP;
    for (size_t i = 0; i < N; i++)
      movedP[i] = p[i] + v[i];
    return move(impl, movedP);
  }

  inline Impl& impl_affine_add_to_self(const ImplV& v) noexcept {
    auto& impl = static_cast<Impl&>(*this);
    auto& p = impl.get_point();
    for (size_t i = 0; i < N; i++)
      p[i] += v[i];
    return impl;
  }

  inline const Impl impl_affine_minus_v(const ImplV& v) const noexcept {
    auto& impl = static_cast<const Impl&>(*this);
    auto& p = impl.get_point();
    ImplP movedP;
    for (size_t i = 0; i < N; i++)
      movedP[i] = p[i] - v[i];
    return move(impl, movedP);
  }

  inline Impl& impl_affine_minus_v_to_self(const ImplV& v) noexcept {
    auto& impl = static_cast<Impl&>(*this);
    auto& p = impl.get_point();
    for (size_t i = 0; i < N; i++)
      p[i] -= v[i];
    return impl;
  }

  template <typename Base, typename Impl, typename ArgList>
  friend struct IMetric;

  inline static F impl_distance(const Impl& x, const Impl& y) noexcept {
    return std::sqrt(distance2(x, y));
  }
};
}  // namespace My
