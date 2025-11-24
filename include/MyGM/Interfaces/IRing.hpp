#pragma once

#include <MyTemplate/SI.hpp>

#include "IAdd.hpp"
#include "IMul.hpp"

namespace My {
template <typename Base, typename Impl>
struct IRing;
}

SI_CombineInterface(My::IRing, My::IAdd, My::IMul);
