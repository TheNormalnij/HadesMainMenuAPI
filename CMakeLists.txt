cmake_minimum_required(VERSION 3.20)

project(HadesMainMenuApi VERSION 1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_definitions(-DEASTL_EASTDC_VSNPRINTF=0)
add_definitions(-DEASTL_DEBUG=0)
add_definitions(-DEASTL_CUSTOM_FLOAT_CONSTANTS_REQUIRED)

add_subdirectory(libs/EASTL-forge1.51)
add_subdirectory(libs/lua-5.2.2)
add_subdirectory(module)

install(TARGETS HadesMainMenuApiLib
        RUNTIME
        DESTINATION ${CMAKE_SOURCE_DIR}/bin
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/module/scripts/
        DESTINATION ${CMAKE_SOURCE_DIR}/bin
)
