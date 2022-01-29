#pragma once
#include "Core/Scripting/Lua/vLuaBooter.h"
#include "Core/Helpers/wiColor.h"

namespace wi::lua
{
    class Color
    {
        public:
            wi::Color color;

            // Class Binder
            static const char className[];
            static Luna<Color>::FunctionType methods[];
            static Luna<Color>::PropertyType properties[];
            Color() {};
            Color(lua_State* L);

            // Instance Binder
            static void Bind(lua_State* L);

            // Class Methods
            int getR(lua_State* L);
            int getG(lua_State* L);
            int getB(lua_State* L);
            int getA(lua_State* L);
            int setR(lua_State* L);
            int setG(lua_State* L);
            int setB(lua_State* L);
            int setA(lua_State* L);
    };
}