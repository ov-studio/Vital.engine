#pragma once
#include "Core/Scripting/vLuaBooter.h"
#include "Core/Helpers/wiMath.h"

namespace wi::lua
{
    class Matrix : public XMFLOAT4X4
    {
        public:
            static const char className[];
            static Luna<Matrix>::FunctionType methods[];
            static Luna<Matrix>::PropertyType properties[];

            Matrix();
            Matrix(const XMMATRIX& matrix);
            Matrix(const XMFLOAT4X4& matrix);
            Matrix(lua_State* L);
            static void Bind(lua_State* L);

            int GetRow(lua_State* L);

            int Translation(lua_State* L);
            int Rotation(lua_State* L);
            int RotationX(lua_State* L);
            int RotationY(lua_State* L);
            int RotationZ(lua_State* L);
            int RotationQuaternion(lua_State* L);
            int Scale(lua_State* L);
            int LookTo(lua_State* L);
            int LookAt(lua_State* L);

            int multiply(lua_State* L);
            int add(lua_State* L);
            int transpose(lua_State* L);
            int inverse(lua_State* L);
    };
}
