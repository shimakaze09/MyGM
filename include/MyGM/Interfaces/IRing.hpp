#pragma once

#include <MyTemplate/SI.hpp>

#include "IAdd.hpp"
#include "IMul.hpp"

namespace Smkz {
template <typename Base, typename Impl>
struct IRing;
}

SI_CombineInterface(Smkz::IRing, Smkz::IAdd, Smkz::IMul);
