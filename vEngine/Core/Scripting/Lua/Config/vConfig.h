#pragma once
#include "Core/Scripting/Lua/vLuaBooter.h"

namespace wi::lua
{
    class Config
    {
        public:
            // Library Binder
            static const char libraryName[];
            static const luaL_Reg libraryFunctions[];

            // Instance Binder
            static void Bind(lua_State* L);

            // Library Methods
            static int setGameSpeed(lua_State* L);
            static int getGameSpeed(lua_State* L);
            static int setShadowProps2D(lua_State* L);
            static int setShadowPropsCube(lua_State* L);
            static int setVSyncEnabled(lua_State* L);
            static int setOcclusionCullingEnabled(lua_State* L);
    };
}