//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "LuaGamemodeFunctionDefs.h"
#include "LuaMenuScreenDefs.h"

class lua_State;

class LuaManager {
  public:
    static void Initialize(lua_State *state) {
        luaState = state;

        LuaGamemodeFunctionDefs::Load(state);
        LuaMenuScreenFunctionDefs::Load(state);
    }

    static lua_State *GetLuaState() { return luaState; };

  private:
    static inline lua_State *luaState{};
};
