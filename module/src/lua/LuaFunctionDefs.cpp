//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"
#include "LuaFunctionDefs.h"

extern "C" {
    #include <lua/lauxlib.h>
    #include <lua/lua.h>
    #include <lua/lualib.h>
}

void LuaFunctionDefs::Load(lua_State* L) {
    #define REGISTER(fun) lua_register(L, #fun, fun)

    #undef REGISTER
}
