//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"

#include <memory>
#include "../include/HadesModApi.h"
#include "HookTable.h"
#include "MainMenuHandler.h"

static std::unique_ptr<MainMenuHandler> mainMenuHandler;

HADES_MOD_API void _cdecl HadesModLuaCreated(lua_State *luaState) {};

HADES_MOD_API bool _cdecl HadesModInit(const IModApi *modApi) {
    if (modApi->version < MOD_API_VERSION)
        return false;

    HookTable::Instance().Init(modApi->GetSymbolAddress);

    mainMenuHandler = std::make_unique<MainMenuHandler>();
    return true;
};

HADES_MOD_API bool _cdecl HadesModStart() { return true; };

HADES_MOD_API bool _cdecl HadesModStop() { return true; };
