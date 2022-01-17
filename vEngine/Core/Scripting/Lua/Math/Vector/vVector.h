#pragma once
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
            int quatNormalize(lua_State* L);
            int clamp(lua_State* L);
            int saturate(lua_State* L);
            int lerp(lua_State* L);
            int quatSlerp(lua_State* L);
            int dot(lua_State* L);
            int cross(lua_State* L);
            int multiply(lua_State* L);
            int quatMultiply(lua_State* L);
            int add(lua_State* L);
            int subtract(lua_State* L);
            int quatFromRollPitchYaw(lua_State* L);
    };
}
