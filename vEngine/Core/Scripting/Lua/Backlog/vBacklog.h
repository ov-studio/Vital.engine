#pragma once
#include "Core/Scripting/vLuaBooter.h"

namespace wi::lua
{
    class Backlog
    {
        public:
            static const char className[];
            static Luna<Texture>::FunctionType methods[];
            static Luna<Texture>::PropertyType properties[];
            Backlog(lua_State* L) {};

            static void Bind(lua_State* L);
    };
}