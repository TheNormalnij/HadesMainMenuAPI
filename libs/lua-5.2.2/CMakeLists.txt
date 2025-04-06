
project(lua)

set(CORE_H
	lua/lapi.h
	lua/lctype.h
	lua/ldebug.h
	lua/ldo.h 
	lua/lfunc.h 
	lua/lgc.h 
	lua/lmem.h 
	lua/lobject.h 
	lua/lopcodes.h 
	lua/lstate.h 
	lua/lstring.h 
	lua/ltable.h 
	lua/ltm.h 
	lua/lvm.h
	lua/lzio.h
	lua/lcode.h
	lua/llex.h 
	lua/llimits.h
	lua/lparser.h 
	lua/lundump.h 
	lua/lua.h
	lua/luaconf.h
	)
set(CORE_C
	lua/lctype.c 
	lua/ldebug.c 
	lua/ldo.c 
	lua/lfunc.c 
	lua/lgc.c 
	lua/lmem.c 
	lua/lobject.c 
	lua/lopcodes.c 
	lua/lstate.c 
	lua/lstring.c 
	lua/ltable.c 
	lua/ltm.c 
	lua/lvm.c 
	lua/lzio.c 
	lua/lcode.c 
	lua/lapi.c 
	lua/lundump.c 
	lua/lparser.c 
	lua/ldump.c 
	lua/llex.c 
	)
set(LIBS 
	lua/lualib.h
	lua/lauxlib.h
	lua/lauxlib.c 
	lua/lbaselib.c 
	lua/lbitlib.c 
	lua/lcorolib.c 
	lua/ldblib.c 
	lua/liolib.c 
	lua/lmathlib.c 
	lua/loslib.c 
	lua/lstrlib.c 
	lua/ltablib.c 
	lua/loadlib.c 
	lua/linit.c)
source_group(core_h FILES ${CORE_H})
source_group(core_c FILES ${CORE_C})
source_group(libs FILES ${LIBS})


add_library(liblua SHARED ${CORE_H} ${CORE_C} ${LIBS})
set_target_properties(liblua PROPERTIES OUTPUT_NAME "lua52")
target_include_directories(liblua PUBLIC ./)

target_compile_definitions(liblua PRIVATE LUA_BUILD_AS_DLL)