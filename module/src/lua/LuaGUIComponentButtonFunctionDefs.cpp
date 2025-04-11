//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"

#include "LuaGUIComponentButtonFunctionDefs.h"
#include "LuaMenuScreenDefs.h"

#include "interface/GUIComponentButton.h"

#include "WrapperClasses.h"
#include "HookedClassFactory.h"
#include "LuaCallback.h"

// GUIComponentButton CreateGUIComponentButton(MenuScreen parent)
static int CreateGUIComponentButton(lua_State* L) {
    auto *menuWrapper = checkclass<GuiMenuScreenUserData>(L, 1);
    auto *gamemodeBtn = HookedClassFactory::Create<SGG::GUIComponentButton, SGG::MenuScreen *>(menuWrapper->Get());
    gamemodeBtn->SetParent(menuWrapper->Get());
    menuWrapper->Get()->AddComponent(gamemodeBtn);

    GuiComponentButtonUserData *wrapper = NewUserData<GuiComponentButtonUserData>(L);
    wrapper->Set(gamemodeBtn);

    return 1;
}

static const luaL_Reg button_mt[] = {
    //
    {nullptr, nullptr}
    //
};


void LuaGUIComponentButtonFunctionDefs::Load(lua_State *L) {
    lua_register(L, "CreateGUIComponentButton", CreateGUIComponentButton);
    RegisterLuaClass(L, button_mt, GuiComponentButtonUserData::LuaClassMeta);
}
