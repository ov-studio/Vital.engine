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
        lunamethod(Vector, quaternionNormalize),
        lunamethod(Vector, add),
        lunamethod(Vector, subtract),
        lunamethod(Vector, multiply),
        lunamethod(Vector, dot),
        lunamethod(Vector, cross),
        lunamethod(Vector, lerp),
        lunamethod(Vector, slerp),
        lunamethod(Vector, clamp),
        lunamethod(Vector, normalize),
        lunamethod(Vector, quaternionMultiply),
        lunamethod(Vector, quaternionFromRollPitchYaw),
        { NULL, NULL }
    }
    Luna<Vector>::PropertyType Vector::properties[] = {
        { NULL, NULL }
    }
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
        if (argc < 1)
        {
            wi::lua::SError(L, "Syntax: vector:setX(float value)");
            return 0
        }
        x = wi::lua::SGetFloat(L, 1);
        return 1;
    }
    int Vector::setY(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc < 1)
        {
            wi::lua::SError(L, "Syntax: vector:setY(float value)");
            return 0
        }
        y = wi::lua::SGetFloat(L, 1);
        return 1;
    }
    int Vector::setZ(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc < 1)
        {
            wi::lua::SError(L, "Syntax: vector:setZ(float value)");
            return 0
        }
        z = wi::lua::SGetFloat(L, 1);
        return 1;
    }
    int Vector::setW(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc < 1)
        {
            wi::lua::SError(L, "Syntax: vector:setW(float value)");
            return 0
        }
        w = wi::lua::SGetFloat(L, 1);
        return 1;
    }


    // TODO: .... 
    int Vector::transform(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* vec = Luna<Vector>::lightcheck(L, 1);
            Matrix_BindLua* mat = Luna<Matrix_BindLua>::lightcheck(L, 2);
            if (vec && mat)
            {
                Luna<Vector>::push(L, new Vector(XMVector4Transform(XMLoadFloat4(vec), XMLoadFloat4x4(mat))));
                return 1;
            }
            else
                wi::lua::SError(L, "transform(Vector vec, Matrix matrix) argument types mismatch!");
        }
        else
            wi::lua::SError(L, "transform(Vector vec, Matrix matrix) not enough arguments!");
        return 0;
    }
    int Vector::transformNormal(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* vec = Luna<Vector>::lightcheck(L, 1);
            Matrix_BindLua* mat = Luna<Matrix_BindLua>::lightcheck(L, 2);
            if (vec && mat)
            {
                Luna<Vector>::push(L, new Vector(XMVector3TransformNormal(XMLoadFloat4(vec), XMLoadFloat4x4(mat))));
                return 1;
            }
            else
                wi::lua::SError(L, "transformNormal(Vector vec, Matrix matrix) argument types mismatch!");
        }
        else
            wi::lua::SError(L, "transformNormal(Vector vec, Matrix matrix) not enough arguments!");
        return 0;
    }
    int Vector::transformCoord(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* vec = Luna<Vector>::lightcheck(L, 1);
            Matrix_BindLua* mat = Luna<Matrix_BindLua>::lightcheck(L, 2);
            if (vec && mat)
            {
                Luna<Vector>::push(L, new Vector(XMVector3TransformCoord(XMLoadFloat4(vec), XMLoadFloat4x4(mat))));
                return 1;
            }
            else
                wi::lua::SError(L, "transformCoord(Vector vec, Matrix matrix) argument types mismatch!");
        }
        else
            wi::lua::SError(L, "transformCoord(Vector vec, Matrix matrix) not enough arguments!");
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
    int Vector::quaternionNormalize(lua_State* L)
    {
        Luna<Vector>::push(L, new Vector(XMQuaternionNormalize(XMLoadFloat4(this))));
        return 1;
    }
    int Vector::clamp(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            float a = wi::lua::SGetFloat(L, 1);
            float b = wi::lua::SGetFloat(L, 2);
            Luna<Vector>::push(L, new Vector(XMVectorClamp(XMLoadFloat4(this), XMVectorSet(a, a, a, a), XMVectorSet(b, b, b, b))));
            return 1;
        }
        else
            wi::lua::SError(L, "clamp(float min,max) not enough arguments!");
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
        if (argc > 2)
        {
            Vector* v1 = Luna<Vector>::lightcheck(L, 1);
            Vector* v2 = Luna<Vector>::lightcheck(L, 2);
            float t = wi::lua::SGetFloat(L, 3);
            if (v1 && v2)
            {
                Luna<Vector>::push(L, new Vector(XMVectorLerp(XMLoadFloat4(v1), XMLoadFloat4(v2), t)));
                return 1;
            }
        }
        wi::lua::SError(L, "lerp(Vector v1,v2, float t) not enough arguments!");
        return 0;
    }
    int Vector::slerp(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 2)
        {
            Vector* v1 = Luna<Vector>::lightcheck(L, 1);
            Vector* v2 = Luna<Vector>::lightcheck(L, 2);
            float t = wi::lua::SGetFloat(L, 3);
            if (v1 && v2)
            {
                Luna<Vector>::push(L, new Vector(XMQuaternionSlerp(XMLoadFloat4(v1), XMLoadFloat4(v2), t)));
                return 1;
            }
        }
        wi::lua::SError(L, "QuaternionSlerp(Vector v1,v2, float t) not enough arguments!");
        return 0;
    }
    int Vector::dot(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* v1 = Luna<Vector>::lightcheck(L, 1);
            Vector* v2 = Luna<Vector>::lightcheck(L, 2);
            if (v1 && v2)
            {
                wi::lua::SSetFloat(L, XMVectorGetX(XMVector3Dot(XMLoadFloat4(v1), XMLoadFloat4(v2))));
                return 1;
            }
        }
        wi::lua::SError(L, "dot(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::cross(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* v1 = Luna<Vector>::lightcheck(L, 1);
            Vector* v2 = Luna<Vector>::lightcheck(L, 2);
            if (v1 && v2)
            {
                Luna<Vector>::push(L, new Vector(XMVector3Cross(XMLoadFloat4(v1), XMLoadFloat4(v2))));
                return 1;
            }
        }
        wi::lua::SError(L, "cross(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::multiply(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* v1 = Luna<Vector>::lightcheck(L, 1);
            Vector* v2 = Luna<Vector>::lightcheck(L, 2);
            if (v1 && v2)
            {
                Luna<Vector>::push(L, new Vector(XMVectorMultiply(XMLoadFloat4(v1), XMLoadFloat4(v2))));
                return 1;
            }
            else if (v1)
            {
                Luna<Vector>::push(L, new Vector(XMLoadFloat4(v1) * wi::lua::SGetFloat(L, 2)));
                return 1;
            }
            else if (v2)
            {
                Luna<Vector>::push(L, new Vector(wi::lua::SGetFloat(L, 1) * XMLoadFloat4(v2)));
                return 1;
            }
        }
        wi::lua::SError(L, "multiply(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::add(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* v1 = Luna<Vector>::lightcheck(L, 1);
            Vector* v2 = Luna<Vector>::lightcheck(L, 2);
            if (v1 && v2)
            {
                Luna<Vector>::push(L, new Vector(XMVectorAdd(XMLoadFloat4(v1), XMLoadFloat4(v2))));
                return 1;
            }
        }
        wi::lua::SError(L, "add(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::subtract(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* v1 = Luna<Vector>::lightcheck(L, 1);
            Vector* v2 = Luna<Vector>::lightcheck(L, 2);
            if (v1 && v2)
            {
                Luna<Vector>::push(L, new Vector(XMVectorSubtract(XMLoadFloat4(v1), XMLoadFloat4(v2))));
                return 1;
            }
        }
        wi::lua::SError(L, "subtract(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::quaternionMultiply(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* v1 = Luna<Vector>::lightcheck(L, 1);
            Vector* v2 = Luna<Vector>::lightcheck(L, 2);
            if (v1 && v2)
            {
                Luna<Vector>::push(L, new Vector(XMQuaternionMultiply(XMLoadFloat4(v1), XMLoadFloat4(v2))));
                return 1;
            }
        }
        wi::lua::SError(L, "quaternionMultiply(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::quaternionFromRollPitchYaw(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 0)
        {
            Vector* v1 = Luna<Vector>::lightcheck(L, 1);
            if (v1)
            {
                Luna<Vector>::push(L, new Vector(XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat4(v1))));
                return 1;
            }
        }
        wi::lua::SError(L, "quaternionFromRollPitchYaw(Vector rotXYZ) not enough arguments!");
        return 0;
    }
}
