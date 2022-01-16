#include "Core/Scripting/Lua/Math/vMath.h"

namespace wi::lua
{
    const char Vector::className[] = "vector";
    Luna<Vector>::FunctionType Vector::methods[] = {
        lunamethod(Vector, GetX),
        lunamethod(Vector, GetY),
        lunamethod(Vector, GetZ),
        lunamethod(Vector, GetW),
        lunamethod(Vector, SetX),
        lunamethod(Vector, SetY),
        lunamethod(Vector, SetZ),
        lunamethod(Vector, SetW),
        lunamethod(Vector, Transform),
        lunamethod(Vector, TransformNormal),
        lunamethod(Vector, TransformCoord),
        lunamethod(Vector, Length),
        lunamethod(Vector, Normalize),
        lunamethod(Vector, QuaternionNormalize),
        lunamethod(Vector, Add),
        lunamethod(Vector, Subtract),
        lunamethod(Vector, Multiply),
        lunamethod(Vector, Dot),
        lunamethod(Vector, Cross),
        lunamethod(Vector, Lerp),
        lunamethod(Vector, Slerp),
        lunamethod(Vector, Clamp),
        lunamethod(Vector, Normalize),
        lunamethod(Vector, QuaternionMultiply),
        lunamethod(Vector, QuaternionFromRollPitchYaw),
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

    int Vector::GetX(lua_State* L)
    {
        wi::lua::SSetFloat(L, x);
        return 1;
    }
    int Vector::GetY(lua_State* L)
    {
        wi::lua::SSetFloat(L, y);
        return 1;
    }
    int Vector::GetZ(lua_State* L)
    {
        wi::lua::SSetFloat(L, z);
        return 1;
    }
    int Vector::GetW(lua_State* L)
    {
        wi::lua::SSetFloat(L, w);
        return 1;
    }

    int Vector::SetX(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 0)
        {
            x = wi::lua::SGetFloat(L, 1);
        }
        else
            wi::lua::SError(L, "SetX(float value) not enough arguments!");
        return 0;
    }
    int Vector::SetY(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 0)
        {
            y = wi::lua::SGetFloat(L, 1);
        }
        else
            wi::lua::SError(L, "SetY(float value) not enough arguments!");
        return 0;
    }
    int Vector::SetZ(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 0)
        {
            z = wi::lua::SGetFloat(L, 1);
        }
        else
            wi::lua::SError(L, "SetZ(float value) not enough arguments!");
        return 0;
    }
    int Vector::SetW(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 0)
        {
            w = wi::lua::SGetFloat(L, 1);
        }
        else
            wi::lua::SError(L, "SetW(float value) not enough arguments!");
        return 0;
    }

    int Vector::Transform(lua_State* L)
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
                wi::lua::SError(L, "Transform(Vector vec, Matrix matrix) argument types mismatch!");
        }
        else
            wi::lua::SError(L, "Transform(Vector vec, Matrix matrix) not enough arguments!");
        return 0;
    }
    int Vector::TransformNormal(lua_State* L)
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
                wi::lua::SError(L, "TransformNormal(Vector vec, Matrix matrix) argument types mismatch!");
        }
        else
            wi::lua::SError(L, "TransformNormal(Vector vec, Matrix matrix) not enough arguments!");
        return 0;
    }
    int Vector::TransformCoord(lua_State* L)
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
                wi::lua::SError(L, "TransformCoord(Vector vec, Matrix matrix) argument types mismatch!");
        }
        else
            wi::lua::SError(L, "TransformCoord(Vector vec, Matrix matrix) not enough arguments!");
        return 0;
    }
    int Vector::Length(lua_State* L)
    {
        wi::lua::SSetFloat(L, XMVectorGetX(XMVector3Length(XMLoadFloat4(this))));
        return 1;
    }
    int Vector::Normalize(lua_State* L)
    {
        Luna<Vector>::push(L, new Vector(XMVector3Normalize(XMLoadFloat4(this))));
        return 1;
    }
    int Vector::QuaternionNormalize(lua_State* L)
    {
        Luna<Vector>::push(L, new Vector(XMQuaternionNormalize(XMLoadFloat4(this))));
        return 1;
    }
    int Vector::Clamp(lua_State* L)
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
            wi::lua::SError(L, "Clamp(float min,max) not enough arguments!");
        return 0;
    }
    int Vector::Saturate(lua_State* L)
    {
        Luna<Vector>::push(L, new Vector(XMVectorSaturate(XMLoadFloat4(this))));
        return 1;
    }



    int Vector::Dot(lua_State* L)
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
        wi::lua::SError(L, "Dot(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::Cross(lua_State* L)
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
        wi::lua::SError(L, "Cross(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::Multiply(lua_State* L)
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
        wi::lua::SError(L, "Multiply(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::Add(lua_State* L)
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
        wi::lua::SError(L, "Add(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::Subtract(lua_State* L)
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
        wi::lua::SError(L, "Subtract(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::Lerp(lua_State* L)
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
        wi::lua::SError(L, "Lerp(Vector v1,v2, float t) not enough arguments!");
        return 0;
    }


    int Vector::QuaternionMultiply(lua_State* L)
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
        wi::lua::SError(L, "QuaternionMultiply(Vector v1,v2) not enough arguments!");
        return 0;
    }
    int Vector::QuaternionFromRollPitchYaw(lua_State* L)
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
        wi::lua::SError(L, "QuaternionFromRollPitchYaw(Vector rotXYZ) not enough arguments!");
        return 0;
    }
    int Vector::Slerp(lua_State* L)
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
}
