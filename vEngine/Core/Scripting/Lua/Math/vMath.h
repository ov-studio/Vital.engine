#pragma once
#include "vCommon.h"
#include "Core/Scripting/vLuaBooter.h"
#include "Core/Helpers/wiMath.h"

namespace wi::lua
{
    class Vector : public XMFLOAT4
    {
        public:
            // Class Binder
            static const char className[];
            static Luna<Vector>::FunctionType methods[];
            static Luna<Vector>::PropertyType properties[];
            Vector();
            Vector(const XMFLOAT4& vector);
            Vector(const XMVECTOR& vector);
            Vector(lua_State* L);
            static void Bind(lua_State* L);

            // Class Methods
            int getX(lua_State* L);
            int getY(lua_State* L);
            int getZ(lua_State* L);
            int getW(lua_State* L);
            int setX(lua_State* L);
            int setY(lua_State* L);
            int setZ(lua_State* L);
            int setW(lua_State* L);
            int transform(lua_State* L);
            int transformNormal(lua_State* L);
            int transformCoord(lua_State* L);
            int length(lua_State* L);
            int normalize(lua_State* L);
            int quaternionNormalize(lua_State* L);
            int clamp(lua_State* L);
            int saturate(lua_State* L);
            int quatSlerp(lua_State* L);
            int slerp(lua_State* L);
            int dot(lua_State* L);
            int cross(lua_State* L);
            int multiply(lua_State* L);
            int quatMultiply(lua_State* L);
            int add(lua_State* L);
            int subtract(lua_State* L);
            int quatFromRollPitchYaw(lua_State* L);
    };

    class Matrix_BindLua : public XMFLOAT4X4
    {
        public:
            static const char className[];
            static Luna<Matrix_BindLua>::FunctionType methods[];
            static Luna<Matrix_BindLua>::PropertyType properties[];

            Matrix_BindLua();
            Matrix_BindLua(const XMMATRIX& matrix);
            Matrix_BindLua(const XMFLOAT4X4& matrix);
            Matrix_BindLua(lua_State* L);
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
            int Transpose(lua_State* L);
            int Inverse(lua_State* L);
    };
}
