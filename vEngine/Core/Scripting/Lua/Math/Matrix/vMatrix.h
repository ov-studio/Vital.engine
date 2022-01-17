#pragma once
#include "Core/Scripting/vLuaBooter.h"
#include "Core/Helpers/wiMath.h"

namespace wi::lua
{
    class Matrix : public XMFLOAT4X4
    {
        public:
            // Class Binder
            static const char className[];
            static Luna<Matrix>::FunctionType methods[];
            static Luna<Matrix>::PropertyType properties[];
            Matrix();
            Matrix(const XMMATRIX& matrix);
            Matrix(const XMFLOAT4X4& matrix);
            Matrix(lua_State* L);
            static void Bind(lua_State* L);

            // Class Methods
            int getRow(lua_State* L);
            int translate(lua_State* L);
            int rotate(lua_State* L);
            int rotateX(lua_State* L);
            int rotateY(lua_State* L);
            int rotateZ(lua_State* L);
            int quatRotate(lua_State* L);
            int scale(lua_State* L);
            int lookTo(lua_State* L);
            int lookAt(lua_State* L);
            int multiply(lua_State* L);
            int add(lua_State* L);
            int transpose(lua_State* L);
            int inverse(lua_State* L);
    };
}
