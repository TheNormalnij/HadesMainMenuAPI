//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"

#include "LuaGUIComponentButtonFunctionDefs.h"
#include "LuaMenuScreenDefs.h"

#include "interface/GUIComponentButton.h"

#include "lua/classes/WrapperClasses.h"
#include "HookedClassFactory.h"
#include "lua/helpers/LuaCallback.h"
#include "lua/LuaManager.h"

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

static int SetText(lua_State *L) {
    auto *wrapper = checkclass<GuiComponentButtonUserData>(L, 1);
    const char *text = luaL_checkstring(L, 2);
    if (!text) {
        return luaL_error(L, "Argument 2 should be text");
    }
    wrapper->Get()->SetText(text);
    return 0;
}

static int AddActivationHandler(lua_State *L) {
    auto *wrapper = checkclass<GuiComponentButtonUserData>(L, 1);
    if (!lua_isfunction(L, 2)) {
        return luaL_error(L, "Argument 2 must be a function");
    }

    LuaCallback cb{L, 2};
    wrapper->Get()->GetActivateAction().AddCallBack([cb, L]() {
        cb.PushFunction(L);
        LuaManager::lua_pcallk(L, 0, 0, 0, 0, 0);
    });

    return 0;
}

static const luaL_Reg button_mt[] = {
    //
    {"SetText", SetText},
    {"AddActivationHandler", AddActivationHandler},
    {nullptr, nullptr}
    //
};

void LuaGUIComponentButtonFunctionDefs::Load(lua_State *L) {
    lua_register(L, "CreateGUIComponentButton", CreateGUIComponentButton);
    RegisterLuaClass(L, button_mt, GuiComponentButtonUserData::LuaClassMeta);
}
