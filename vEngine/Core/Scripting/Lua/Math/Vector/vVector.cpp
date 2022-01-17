#include "Core/Scripting/Lua/Math/vMath.h"

namespace wi::lua
{
    // Class Binder
    const char Vector::className[] = "vector";
    Luna<Vector>::FunctionType Vector::methods[] = {
        lunamethod(Vector, getX),
        lunamethod(Vector, getY),
        lunamethod(Vector, getZ),
        lunamethod(Vector, getW),
        lunamethod(Vector, setX),
        lunamethod(Vector, setY),
        lunamethod(Vector, setZ),
        lunamethod(Vector, setW),
        lunamethod(Vector, transform),
        lunamethod(Vector, transformNormal),
        lunamethod(Vector, transformCoord),
        lunamethod(Vector, length),
        lunamethod(Vector, normalize),
        lunamethod(Vector, quatNormalize),
        lunamethod(Vector, clamp),
        lunamethod(Vector, saturate),
        lunamethod(Vector, lerp),
        lunamethod(Vector, quatSlerp),
        lunamethod(Vector, dot),
        lunamethod(Vector, cross),
        lunamethod(Vector, multiply),
        lunamethod(Vector, quatMultiply),
        lunamethod(Vector, add),
        lunamethod(Vector, subtract),
        lunamethod(Vector, quatFromRollPitchYaw),
        { NULL, NULL }
    };
    Luna<Vector>::PropertyType Vector::properties[] = {
        { NULL, NULL }
    };
    Vector::Vector()
    {
        x = 0; y = 0; z = 0; w = 0;
    }
    Vector::Vector(const XMFLOAT4& vector)
    {
        x = vector.x; y = vector.y;
        z = vector.z; w = vector.w;
    }
    Vector::Vector(const XMVECTOR& vector)
    {
        XMStoreFloat4(this, vector);
    }
    Vector::Vector(lua_State* L)
    {
        x = 0; y = 0; z = 0; w = 0;
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 0)
        {
            x = wi::lua::SGetFloat(L, 1);
            if (argc > 1)
            {
                y = wi::lua::SGetFloat(L, 2);
                if (argc > 2)
                {
                    z = wi::lua::SGetFloat(L, 3);
                    if (argc > 3)
                    {
                        w = wi::lua::SGetFloat(L, 4);
                    }
                }
            }
        }
    }
    void Vector::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            Luna<Vector>::Register(L, "vEngine");
        }
    }

    // Class Methods
    int Vector::getX(lua_State* L)
    {
        wi::lua::SSetFloat(L, x);
        return 1;
    }
    int Vector::getY(lua_State* L)
    {
        wi::lua::SSetFloat(L, y);
        return 1;
    }
    int Vector::getZ(lua_State* L)
    {
        wi::lua::SSetFloat(L, z);
        return 1;
    }
    int Vector::getW(lua_State* L)
    {
        wi::lua::SSetFloat(L, w);
        return 1;
    }
    int Vector::setX(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            x = wi::lua::SGetFloat(L, 1);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vector:setX(float value)");
        return 0;
    }
    int Vector::setY(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            y = wi::lua::SGetFloat(L, 1);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vector:setY(float value)");
        return 0;
    }
    int Vector::setZ(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            z = wi::lua::SGetFloat(L, 1);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vector:setZ(float value)");
        return 0;
    }
    int Vector::setW(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            w = wi::lua::SGetFloat(L, 1);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vector:setW(float value)");
        return 0;
    }
    int Vector::transform(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Matrix* cMatrix = Luna<Matrix>::lightcheck(L, 1);
            if (cMatrix)
            {
                Luna<Vector>::push(L, new Vector(XMVector4Transform(XMLoadFloat4(this), XMLoadFloat4x4(cMatrix))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:transform(userdata matrix)");
        return 0;
    }
    int Vector::transformNormal(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Matrix* cMatrix = Luna<Matrix>::lightcheck(L, 1);
            if (cMatrix)
            {
                Luna<Vector>::push(L, new Vector(XMVector3TransformNormal(XMLoadFloat4(this), XMLoadFloat4x4(cMatrix))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:transformNormal(userdata matrix)");
        return 0;
    }
    int Vector::transformCoord(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Matrix* cMatrix = Luna<Matrix>::lightcheck(L, 1);
            if (cMatrix)
            {
                Luna<Vector>::push(L, new Vector(XMVector3TransformCoord(XMLoadFloat4(this), XMLoadFloat4x4(cMatrix))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:transformCoord(userdata matrix)");
        return 0;
    }
    int Vector::length(lua_State* L)
    {
        wi::lua::SSetFloat(L, XMVectorGetX(XMVector3Length(XMLoadFloat4(this))));
        return 1;
    }
    int Vector::normalize(lua_State* L)
    {
        Luna<Vector>::push(L, new Vector(XMVector3Normalize(XMLoadFloat4(this))));
        return 1;
    }
    int Vector::quatNormalize(lua_State* L)
    {
        Luna<Vector>::push(L, new Vector(XMQuaternionNormalize(XMLoadFloat4(this))));
        return 1;
    }
    int Vector::clamp(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 2)
        {
            float a = wi::lua::SGetFloat(L, 1);
            float b = wi::lua::SGetFloat(L, 2);
            Luna<Vector>::push(L, new Vector(XMVectorClamp(XMLoadFloat4(this), XMVectorSet(a, a, a, a), XMVectorSet(b, b, b, b))));
            return 1;
        }
        wi::lua::SError(L, "Syntax: vector:clamp(float minValue, float maxValue)");
        return 0;
    }
    int Vector::saturate(lua_State* L)
    {
        Luna<Vector>::push(L, new Vector(XMVectorSaturate(XMLoadFloat4(this))));
        return 1;
    }
    int Vector::lerp(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 2)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            float lerpRate = wi::lua::SGetFloat(L, 2);
            if (cVector)
            {
                Luna<Vector>::push(L, new Vector(XMVectorLerp(XMLoadFloat4(this), XMLoadFloat4(cVector), lerpRate)));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:lerp(userdata vector, float lerpRate)");
        return 0;
    }
    int Vector::quatSlerp(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 2)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            float lerpRate = wi::lua::SGetFloat(L, 2);
            if (cVector)
            {
                Luna<Vector>::push(L, new Vector(XMQuaternionSlerp(XMLoadFloat4(this), XMLoadFloat4(cVector), lerpRate)));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:quatSlerp(userdata vector, float lerpRate)");
        return 0;
    }
    int Vector::dot(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                wi::lua::SSetFloat(L, XMVectorGetX(XMVector3Dot(XMLoadFloat4(this), XMLoadFloat4(cVector))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:dot(userdata vector)");
        return 0;
    }
    int Vector::cross(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                Luna<Vector>::push(L, new Vector(XMVector3Cross(XMLoadFloat4(this), XMLoadFloat4(cVector))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:cross(userdata vector)");
        return 0;
    }
    int Vector::multiply(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                Luna<Vector>::push(L, new Vector(XMVectorMultiply(XMLoadFloat4(this), XMLoadFloat4(cVector))));
                return 1;
            }
            else
            {
                Luna<Vector>::push(L, new Vector(XMLoadFloat4(this) * wi::lua::SGetFloat(L, 1)));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:multiply([userdata vector, float multiplier])");
        return 0;
    }
    int Vector::quatMultiply(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                Luna<Vector>::push(L, new Vector(XMQuaternionMultiply(XMLoadFloat4(this), XMLoadFloat4(cVector))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:quatMultiply(userdata vector)");
        return 0;
    }
    int Vector::add(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                Luna<Vector>::push(L, new Vector(XMVectorAdd(XMLoadFloat4(this), XMLoadFloat4(cVector))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:add(userdata vector)");
        return 0;
    }
    int Vector::subtract(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                Luna<Vector>::push(L, new Vector(XMVectorSubtract(XMLoadFloat4(this), XMLoadFloat4(cVector))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:subtract(userdata vector)");
        return 0;
    }
    int Vector::quatFromRollPitchYaw(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                Luna<Vector>::push(L, new Vector(XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat4(cVector))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: vector:quatFromRollPitchYaw()");
        return 0;
    }
}
