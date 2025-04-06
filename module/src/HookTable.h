//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "../include/HadesModApi.h"

struct HookTable {
    static HookTable& Instance();
    void Init(IModApi::GetSymbolAddress_t GetSymbolAddress);

    uintptr_t MenuScreen_constructor;
    uintptr_t MenuScreen_costructor_ScreenManager;
    uintptr_t MainMenuScreen_MainMenuScreen;
    uintptr_t GUIComponentButton_GUIComponentButton;
    uintptr_t vector8x8_push;
    uintptr_t GUIComponentReflectionHelper_ReflectComponent_GUIComponentButton;
};
