//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"

#include "LuaMenuScreenDefs.h"

#include "lua.hpp"

#include "interface/GUIComponent.h"
#include "interface/MenuScreen.h"

#include "LuaClass.h"
#include "HookedClassFactory.h"
#include "LibraryComponents.h"
#include "LuaCallback.h"

struct GuiMenuScreenUserData {
    static constexpr const char *LuaClassMeta = "MainMenuApi.MenuScreen";
    static constexpr const char *LuaClassName = "MenuScreen";

    SGG::MenuScreen *pointer;
};

static int CreateMenuScreen(lua_State *L) {
    GuiMenuScreenUserData *menu =
        static_cast<GuiMenuScreenUserData *>(lua_newuserdata(L, sizeof(GuiMenuScreenUserData)));

    luaL_getmetatable(L, "MainMenuApi.MenuScreen");
    lua_setmetatable(L, -2);

    auto *sceenManager = LibraryComponents::Instance()->GetMenuHandler()->GetMainMenu()->GetScreenManager();
    menu->pointer = HookedClassFactory::Create<SGG::MenuScreen>(sceenManager);
    sceenManager->AddScreen(menu->pointer);
    return 1;
}

static int MenuScreenLoadDefenitions(lua_State* L) {
    auto *menuWrapper = checkclass<GuiMenuScreenUserData>(L, 1);

    if (!lua_isstring(L, 2)) {
        return luaL_error(L, "Argument 2 must be a string");
    }

    auto *menu = menuWrapper->pointer;
    menu->GetScreenData().ReadXml(menu, lua_tostring(L, 2));

    return 0;
}

static int MenuScreenCreateBack(lua_State *L) {
    auto *menuWrapper = checkclass<GuiMenuScreenUserData>(L, 1);

    if (!lua_isnumber(L, 2)) {
        return luaL_error(L, "Argument 2 must be a number");
    }

    menuWrapper->pointer->CreateBack((float)lua_tonumber(L, 2));

    return 0;
}

static int MenuScreenCreateBackground(lua_State *L) {
    auto *menuWrapper = checkclass<GuiMenuScreenUserData>(L, 1);

    const char *str = lua_isstring(L, 2) ? lua_tostring(L, 2) : "";
    eastl::string bgName{str};

    menuWrapper->pointer->CreateBackground(&bgName);

    return 0;
}

static int MenuScreenCreateTitleText(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        return luaL_error(L, "Argument 1 must be a MenuScreen");
    }

    auto *menu = static_cast<GuiMenuScreenUserData *>(lua_touserdata(L, 1));
    menu->pointer->CreateTitleText(menu->pointer);

    return 0;
}

static int MenuScreenCreateCancelButton(lua_State *L) {
    auto *menuWrapper = checkclass<GuiMenuScreenUserData>(L, 1);
    menuWrapper->pointer->CreateCancelButton(menuWrapper->pointer);

    if (!lua_isfunction(L, 2)) {
        return luaL_error(L, "Argument 2 must be a function");
    }

    LuaCallback cb{L, 2};

    menuWrapper->pointer->GetCancelButton()->GetActivateAction().AddCallBack([cb, L]() {
        cb.PushFunction(L);
        lua_pcall(L, 0, 0, 0);
    });

    return 0;
}

static int MenuScreenSetLoverInputBlock(lua_State *L) {
    auto *menuWrapper = checkclass<GuiMenuScreenUserData>(L, 1);

    if (!lua_isboolean(L, 2)) {
        return luaL_error(L, "Argument 1 must be a boolean");
    }

    menuWrapper->pointer->SetLoverInputBlock(lua_toboolean(L, 2) == 1);

    return 0;
}

static int MenuScreenClose(lua_State *L) {
    auto *menuWrapper = checkclass<GuiMenuScreenUserData>(L, 1);

    auto *menu = menuWrapper->pointer;
    auto *cancelBtn = menu->GetCancelButton();

    menu->ExitScreen();
    
    // shit
    if (cancelBtn)
        cancelBtn->GetActivateAction().RemoveAll();

    return 0;
}

static const luaL_Reg menuscreen_mt[] = {
    //
    {"Create", CreateMenuScreen},
    {"LoadDefenitions", MenuScreenLoadDefenitions},
    {"CreateBack", MenuScreenCreateBack},
    {"CreateBackground", MenuScreenCreateBackground},
    {"CreateTitleText", MenuScreenCreateTitleText},
    {"CreateCancelButton", MenuScreenCreateCancelButton},
    {"SetLowerInputBlock", MenuScreenSetLoverInputBlock},
    {"Close", MenuScreenClose},
    {nullptr, nullptr}
    //
};

void LuaMenuScreenFunctionDefs::Load(lua_State* L) {
    lua_register(L, "CreateMenuScreen", CreateMenuScreen);
    RegisterLuaClass(L, menuscreen_mt, GuiMenuScreenUserData::LuaClassMeta);
}
