//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "MenuScreen.h"
#include "GUIComponent.h"

#include "HookTable.h"

namespace SGG {

class GUIComponentButton : public GUIComponent {
  public:

    static GUIComponentButton* internal_constructor(MenuScreen *owner) {
        void *pointer = _aligned_malloc(sizeof(GUIComponentButton), std::alignment_of<GUIComponentButton>::value);
        return reinterpret_cast<GUIComponentButton* (*)(void *, MenuScreen *)>(
            HookTable::Instance().GUIComponentButton_GUIComponentButton)(pointer, owner);
    }

  private:
    char pad[0x98];
};
static_assert(sizeof(GUIComponentButton) == 0xA88, "Incorrect SGG::GUIComponentButton size");
} // namespace SGG
