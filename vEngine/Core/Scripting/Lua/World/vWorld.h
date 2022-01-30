#pragma once
#include "Core/Scripting/Lua/vLuaBooter.h"

namespace wi::lua
{
    class World
    {
        public:
            // Library Binder
            static const char libraryName[];
            static const luaL_Reg libraryFunctions[];

            // Instance Binder
            static void Bind(lua_State* L);

            // Library Methods
            static int clearScene(lua_State* L);
    };
}