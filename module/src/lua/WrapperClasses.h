//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "LuaClass.h"

#include "interface/MenuScreen.h"
#include "interface/GuiComponentButton.h"

class GuiMenuScreenUserData : public LuaClassWrapper<SGG::MenuScreen> {
  public:
    static constexpr const char *LuaClassMeta = "MainMenuApi.MenuScreen";
    static constexpr const char *LuaClassName = "MenuScreen";
};

class GuiComponentButtonUserData : public LuaClassWrapper<SGG::GUIComponentButton> {
  public:
    static constexpr const char *LuaClassMeta = "MainMenuApi.GUIComponentButton";
    static constexpr const char *LuaClassName = "GUIComponentButton";
};
