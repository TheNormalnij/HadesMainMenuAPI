//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "lua.hpp"

template <class T> class LuaClassWrapper {
  public:
    using GameType = T;

    void Set(T *data) noexcept { pointer = data; }
    T *Get() const noexcept { return pointer; }

  private:
    T *pointer;
};

template<class T>
static T *NewUserData(lua_State *L) {
    auto *userdata = static_cast<T *>(lua_newuserdata(L, sizeof(T)));
    luaL_getmetatable(L, T::LuaClassMeta);
    lua_setmetatable(L, -2);
    return userdata;
}

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

template <class T> static T *GetUserdata(lua_State *L, int pos) {
    return (T *)luaL_checkudata(L, pos, T::LuaClassMeta);
};

template <class T> static T *checkclass(lua_State *L, int pos) {
    T *ud = GetUserdata<T>(L, pos);
    luaL_argcheck(L, ud != nullptr, pos, T::LuaClassName);
    return ud;
};
