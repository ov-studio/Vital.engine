#pragma once
#include "Core/Scripting/Lua/vLuaBooter.h"
#include "Core/Helpers/wiMath.h"

namespace wi::lua
{
    class Matrix : public XMFLOAT4X4
    {
        public:
            // Library Binder
            static const char libraryName[];
            static const luaL_Reg libraryFunctions[];

            // Class Binder
            static const char className[];
            static Luna<Matrix>::FunctionType methods[];
            static Luna<Matrix>::PropertyType properties[];
            Matrix();
            Matrix(const XMMATRIX& matrix);
            Matrix(const XMFLOAT4X4& matrix);
            Matrix(lua_State* L);

            // Instance Binder
            static void Bind(lua_State* L);

            // Library Methods
            static int translation(lua_State* L);
            static int rotation(lua_State* L);
            static int rotationX(lua_State* L);
            static int rotationY(lua_State* L);
            static int rotationZ(lua_State* L);
            static int quatRotation(lua_State* L);
            static int scaling(lua_State* L);
            static int lookTo(lua_State* L);
            static int lookAt(lua_State* L);

            // Class Methods
            int getRow(lua_State* L);
            int multiply(lua_State* L);
            int add(lua_State* L);
            int transpose(lua_State* L);
            int inverse(lua_State* L);
    };
}
