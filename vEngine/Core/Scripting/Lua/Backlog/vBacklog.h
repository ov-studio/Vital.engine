#pragma once
#include "Core/Scripting/vLuaBooter.h"

namespace wi::lua
{
    class Backlog
    {
        public:
            // Library Binder
            static const char libraryName[];
            static const luaL_Reg libraryFunctions[];

            // Instance Binder
            static void Bind(lua_State* L);

            // Library Methods
            static int clear(lua_State* L);
            static int post(lua_State* L);
            static int isActive(lua_State* L);
            static int setLevel(lua_State* L);
    };
}