#pragma once
#include "Core/Scripting/vLuaBooter.h"

namespace wi::lua
{
    class Backlog
    {
        public:
            // Class Binder
            static const char className[];
            static Luna<Backlog>::FunctionType methods[];
            static Luna<Backlog>::PropertyType properties[];
            Backlog(lua_State* L) {};
            static void Bind(lua_State* L);

            // Class Methods
            int clear(lua_State* L);
            int post(lua_State* L);
            int isActive(lua_State* L);
            int setLevel(lua_State* L);
    };
}