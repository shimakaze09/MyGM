#pragma once

#include "IAdd.h"
#include "IMul.h"

#include <MyTemplate/SI.h>

namespace My {
template <typename Base, typename Impl>
struct IRing;
}  // namespace My

SI_CombineInterface(My::IRing, My::IAdd, My::IMul);
