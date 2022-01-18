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
            int clear(lua_State* L);
            int post(lua_State* L);
            int isActive(lua_State* L);
            int setLevel(lua_State* L);
    };
}