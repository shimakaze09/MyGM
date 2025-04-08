#pragma once

#include "IAdd.h"
#include "IMul.h"

#include <MyTemplate/SI.h>

namespace My {
SI_CombineInterface(IRing, IAdd, IMul);
}
