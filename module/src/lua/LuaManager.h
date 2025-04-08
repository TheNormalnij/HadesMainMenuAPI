//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "LuaFunctionDefs.h"

class lua_State;

class LuaManager {
  public:
    static void Initialize(lua_State *state) {
        LuaFunctionDefs::Load(state);
        luaState = state;
    }

    static lua_State *GetLuaState() { return luaState; };

  private:
    static inline lua_State *luaState{};
};
