//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "../libs/EASTL-forge1.51/string.h"

namespace SGG {
class ComponentData {
  public:
  private:
    bool mCreated;
    eastl::basic_string<char, eastl::allocator_forge> mName;

    char mDef[0x760];
};
static_assert(sizeof(ComponentData) == 0x780, "Incorrect SGG::ComponentData size");
} // namespace SGG