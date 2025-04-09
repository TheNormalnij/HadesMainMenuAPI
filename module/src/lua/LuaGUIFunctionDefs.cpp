//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"

#include "LuaGUIFunctionDefs.h"

#include "lua.hpp"

#include "interface/GUIComponent.h"
#include "interface/MenuScreen.h"

#include "HookedClassFactory.h"
#include "LibraryComponents.h"


struct GuiElementUserData {
    SGG::GUIComponent *pointer;
};

struct GuiMenuScreenUserData {
    SGG::MenuScreen *pointer;
};

static int CreateMenuScreen(lua_State *L) {
    GuiMenuScreenUserData *menu =
        static_cast<GuiMenuScreenUserData *>(lua_newuserdata(L, sizeof(GuiMenuScreenUserData)));

    auto *sceenManager = LibraryComponents::Instance()->GetMenuHandler()->GetMainMenu()->GetScreenManager();
    menu->pointer = HookedClassFactory::Create<SGG::MenuScreen>(sceenManager);
    sceenManager->AddScreen(menu->pointer);
    return 1;
}

static int CreateButton(lua_State *L) {

    return 1;
}

static int MenuScreenLoadDefenitions(lua_State* L) {
    if (!lua_isuserdata(L, 1)) {
        return luaL_error(L, "Argument 1 must be a MenuScreen");
    }

    if (!lua_isstring(L, 2)) {
        return luaL_error(L, "Argument 2 must be a string");
    }

    auto *menu = static_cast<GuiMenuScreenUserData*>(lua_touserdata(L, 1));
    menu->pointer->Load(lua_tostring(L, 2));

    return 0;
}

static int MenuScreenCreateBack(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        return luaL_error(L, "Argument 1 must be a MenuScreen");
    }

    if (!lua_isnumber(L, 2)) {
        return luaL_error(L, "Argument 2 must be a number");
    }

    auto *menu = static_cast<GuiMenuScreenUserData *>(lua_touserdata(L, 1));
    menu->pointer->CreateBack((float)lua_tonumber(L, 2));

    return 0;
}

static int MenuScreenCreateBackground(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        return luaL_error(L, "Argument 1 must be a MenuScreen");
    }

    // TODO make optional
    if (!lua_isstring(L, 2)) {
        return luaL_error(L, "Argument 2 must be a string");
    }

    auto *menu = static_cast<GuiMenuScreenUserData *>(lua_touserdata(L, 1));

    eastl::string bgName{lua_tostring(L, 2)};
    menu->pointer->CreateBackground(&bgName);

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
    if (!lua_isuserdata(L, 1)) {
        return luaL_error(L, "Argument 1 must be a MenuScreen");
    }

    auto *menu = static_cast<GuiMenuScreenUserData *>(lua_touserdata(L, 1));
    menu->pointer->CreateCancelButton(menu->pointer);

    return 0;
}

static int MenuScreenSetLoverInputBlock(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        return luaL_error(L, "Argument 1 must be a MenuScreen");
    }

    if (!lua_isboolean(L, 2)) {
        return luaL_error(L, "Argument 1 must be a boolean");
    }

    auto *menu = static_cast<GuiMenuScreenUserData *>(lua_touserdata(L, 1));
    menu->pointer->SetLoverInputBlock(lua_toboolean(L, 2) == 1);

    return 0;
}

void LuaGUIFunctionDefs::Load(lua_State* L) {
#define REGISTER(fun) lua_register(L, #fun, fun)

    REGISTER(CreateMenuScreen);
    REGISTER(CreateButton);
    REGISTER(MenuScreenLoadDefenitions);
    REGISTER(MenuScreenCreateBack);
    REGISTER(MenuScreenCreateBackground);
    REGISTER(MenuScreenCreateTitleText);
    REGISTER(MenuScreenCreateCancelButton);
    REGISTER(MenuScreenSetLoverInputBlock);

#undef REGISTER
}