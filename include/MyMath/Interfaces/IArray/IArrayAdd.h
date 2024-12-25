//
// Created by Admin on 25/12/2024.
//

#pragma once

#include <MyTemplate/SI.h>
#include "../IAdd.h"
#include "IArray.h"

namespace My {
template <typename Base, typename Impl, typename ArgList>
struct IArrayAdd : SIVT_CRTP<TemplateList<IAdd, IArray>, Base, Impl, ArgList> {
  using N = At_t<ArgList, 1>;

  using SIVT_CRTP<TemplateList<IAdd, IArray>, Base, Impl, ArgList>::SIVT_CRTP;

 private:
  template<typename Base, typename Impl, typename ArgList>
  friend struct IAdd;

  const Impl ImplAdd(const Impl& y) const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    Impl rst{};
    for (size_t i = 0; i < N::value; i++)
      rst[i] = x[i] + y[i];
    return rst;
  }

  Impl& ImplAddToSelf(const Impl& y) noexcept {
    auto& x = static_cast<Impl&>(*this);
    for (size_t i = 0; i < N::value; i++)
      x[i] += y[i];
    return x;
  }

  const Impl ImplAddInverse() const noexcept {
    auto& x = static_cast<const Impl&>(*this);
    Impl rst{};
    for (size_t i = 0; i < N::value; i++)
      rst[i] = -x[i];
    return rst;
  }

  //  const Impl Minus(const Impl& y) const noexcept {
  //    auto& x = static_cast<const Impl&>(*this);
  //    Impl rst{};
  //    for (size_t i = 0; i < N::value; i++)
  //      rst[i] = x[i] - y[i];
  //    return rst;
  //  }
  //
  //  Impl& MinusToSelf(const Impl& y) noexcept {
  //    auto& x = static_cast<Impl&>(*this);
  //    for (size_t i = 0; i < N::value; i++)
  //      x[i] -= y[i];
  //    return x;
  //  }
};
}  // namespace My
