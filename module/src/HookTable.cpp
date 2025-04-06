//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "HookTable.h"

static HookTable g_HookTable{};

HookTable& HookTable::Instance() {
    return g_HookTable; }

void HookTable::Init(IModApi::GetSymbolAddress_t GetSymbolAddress) {
    MenuScreen_constructor = GetSymbolAddress("sgg::MenuScreen::MenuScreen");
    MenuScreen_costructor_ScreenManager = GetSymbolAddress("??0MenuScreen@sgg@@QEAA@PEAVScreenManager@1@@Z");
    MainMenuScreen_MainMenuScreen = GetSymbolAddress("sgg::MainMenuScreen::MainMenuScreen");
    GUIComponentButton_GUIComponentButton = GetSymbolAddress("sgg::GUIComponentButton::GUIComponentButton");
    vector8x8_push = GetSymbolAddress(
        "eastl::stack<sgg::IUndoRedoRecord *,eastl::vector<sgg::IUndoRedoRecord *,eastl::allocator_forge> >::push");
    GUIComponentReflectionHelper_ReflectComponent_GUIComponentButton = GetSymbolAddress("sgg::GUIComponentReflectionHelper::ReflectComponent<sgg::GUIComponentButton *>");
    return;
}
