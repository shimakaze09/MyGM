//
// Created by Admin on 25/12/2024.
//

#pragma once

#include <MyTemplate/List/Typelist.h>
#include <MyTemplate/Num/Num.h>

namespace My {
template <typename ArgList>
using Arg_T = At_t<At_t<ArgList, 0>, 0>;

template <typename ArgList>
constexpr size_t Arg_N = At_t<At_t<ArgList, 0>, 1>::value;

template <typename ArgList>
using Arg_F = At_t<ArgList, 1>;

template <typename ArgList>
using Arg_ImplV = At_t<ArgList, 2>;
}  // namespace My
