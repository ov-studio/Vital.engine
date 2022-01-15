#pragma once
#include "Core/Scripting/vLuaBooter.h"

namespace wi::lua
{
    class Backlog
    {
        public:
            static const char className[];
            static Luna<Backlog>::FunctionType methods[];
            static Luna<Backlog>::PropertyType properties[];
            Backlog(lua_State* L) {};

            static void Bind(lua_State* L);
    };
}