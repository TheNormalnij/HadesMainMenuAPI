//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

namespace SGG {
class ScreenData {
  private:
    char pad_0[0x118];
};

static_assert(sizeof(ScreenData) == 0x118, "Incorrect SGG::ScreenData size");
} // namespace SGG
