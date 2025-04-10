//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

static void RegisterLuaClass(lua_State *L, const luaL_Reg *functions, const char *name) {
    luaL_newmetatable(L, name);
    for (; functions->name != NULL; functions++) {
        lua_pushcfunction(L, functions->func);
        lua_setfield(L, -2, functions->name);
    }

    lua_pushvalue(L, -1); // metatable.__index = metatable
    lua_setfield(L, -2, "__index");

    lua_pop(L, 1);
};

template <class T> static T *checkclass(lua_State *L, int pos) {
    void *ud = luaL_checkudata(L, pos, T::LuaClassMeta);
    luaL_argcheck(L, ud != nullptr, pos, T::LuaClassName);
    return (T *)ud;
}
