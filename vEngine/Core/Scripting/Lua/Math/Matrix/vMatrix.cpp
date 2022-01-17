#include "Core/Scripting/Lua/Math/vMath.h"

namespace wi::lua
{
    const char Matrix::className[] = "matrix";
    Luna<Matrix>::FunctionType Matrix::methods[] = {
        lunamethod(Matrix, GetRow),
        lunamethod(Matrix, Translation),
        lunamethod(Matrix, Rotation),
        lunamethod(Matrix, RotationX),
        lunamethod(Matrix, RotationY),
        lunamethod(Matrix, RotationZ),
        lunamethod(Matrix, RotationQuaternion),
        lunamethod(Matrix, Scale),
        lunamethod(Matrix, LookTo),
        lunamethod(Matrix, LookAt),

        lunamethod(Matrix, add),
        lunamethod(Matrix, multiply),
        lunamethod(Matrix, transpose),
        lunamethod(Matrix, inverse),
        { NULL, NULL }
    };
    Luna<Matrix>::PropertyType Matrix::properties[] = {
        { NULL, NULL }
    }

    Matrix::Matrix()
    {
        std::memcpy(this, &wi::math::IDENTITY_MATRIX, sizeof(wi::math::IDENTITY_MATRIX));
    }
    Matrix::Matrix(const XMFLOAT4X4& matrix)
    {
        std::memcpy(this, &matrix, sizeof(matrix));
    }
    Matrix::Matrix(const XMMATRIX& matrix)
    {
        XMStoreFloat4x4(this, matrix);
    }
    Matrix::Matrix(lua_State* L)
    {
        std::memcpy(this, &wi::math::IDENTITY_MATRIX, sizeof(wi::math::IDENTITY_MATRIX));

        int argc = wi::lua::SGetArgCount(L);

        // fill out all the four rows of the matrix
        for (int i = 0; i < 4; ++i)
        {
            float x = 0.f, y = 0.f, z = 0.f, w = 0.f;
            if (argc > i * 4)
            {
                x = wi::lua::SGetFloat(L, i * 4 + 1);
                if (argc > i * 4 + 1)
                {
                    y = wi::lua::SGetFloat(L, i * 4 + 2);
                    if (argc > i * 4 + 2)
                    {
                        z = wi::lua::SGetFloat(L, i * 4 + 3);
                        if (argc > i * 4 + 3)
                        {
                            w = wi::lua::SGetFloat(L, i * 4 + 4);
                        }
                    }
                }
            }
            this->m[i][0] = x;
            this->m[i][1] = x;
            this->m[i][2] = x;
            this->m[i][3] = x;
        }

    }

    int Matrix::GetRow(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        int row = 0;
        if (argc > 1)
        {
            row = wi::lua::SGetInt(L, 2);
            if (row < 0 || row > 3)
                row = 0;
        }
        XMFLOAT4 r = XMFLOAT4(m[row][0], m[row][1], m[row][2], m[row][3]);
        Luna<Vector>::push(L, new Vector(r));
        return 1;
    }



    int Matrix::Translation(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX mat = XMMatrixIdentity();
        if (argc > 0)
        {
            Vector* vector = Luna<Vector>::lightcheck(L, 1);
            if (vector != nullptr)
            {
                mat = XMMatrixTranslationFromVector(XMLoadFloat4(vector));
            }
        }
        Luna<Matrix>::push(L, new Matrix(mat));
        return 1;
    }

    int Matrix::Rotation(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX mat = XMMatrixIdentity();
        if (argc > 0)
        {
            Vector* vector = Luna<Vector>::lightcheck(L, 1);
            if (vector != nullptr)
            {
                mat = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat4(vector));
            }
        }
        Luna<Matrix>::push(L, new Matrix(mat));
        return 1;
    }

    int Matrix::RotationX(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX mat = XMMatrixIdentity();
        if (argc > 0)
        {
            mat = XMMatrixRotationX(wi::lua::SGetFloat(L, 1));
        }
        Luna<Matrix>::push(L, new Matrix(mat));
        return 1;
    }

    int Matrix::RotationY(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX mat = XMMatrixIdentity();
        if (argc > 0)
        {
            mat = XMMatrixRotationY(wi::lua::SGetFloat(L, 1));
        }
        Luna<Matrix>::push(L, new Matrix(mat));
        return 1;
    }

    int Matrix::RotationZ(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX mat = XMMatrixIdentity();
        if (argc > 0)
        {
            mat = XMMatrixRotationZ(wi::lua::SGetFloat(L, 1));
        }
        Luna<Matrix>::push(L, new Matrix(mat));
        return 1;
    }

    int Matrix::RotationQuaternion(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX mat = XMMatrixIdentity();
        if (argc > 0)
        {
            Vector* vector = Luna<Vector>::lightcheck(L, 1);
            if (vector != nullptr)
            {
                mat = XMMatrixRotationQuaternion(XMLoadFloat4(vector));
            }
        }
        Luna<Matrix>::push(L, new Matrix(mat));
        return 1;
    }

    int Matrix::Scale(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX mat = XMMatrixIdentity();
        if (argc > 0)
        {
            Vector* vector = Luna<Vector>::lightcheck(L, 1);
            if (vector != nullptr)
            {
                mat = XMMatrixScalingFromVector(XMLoadFloat4(vector));
            }
        }
        Luna<Matrix>::push(L, new Matrix(mat));
        return 1;
    }

    int Matrix::LookTo(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* pos = Luna<Vector>::lightcheck(L, 1);
            Vector* dir = Luna<Vector>::lightcheck(L, 2);
            if (pos != nullptr && dir != nullptr)
            {
                XMVECTOR Up;
                if (argc > 3)
                {
                    Vector* up = Luna<Vector>::lightcheck(L, 3);
                    Up = XMLoadFloat4(up);
                }
                else
                    Up = XMVectorSet(0, 1, 0, 0);
                Luna<Matrix>::push(L, new Matrix(XMMatrixLookToLH(XMLoadFloat4(pos), XMLoadFloat4(dir), Up)));
            }
            else
                wi::lua::SError(L, "LookTo(Vector eye, Vector direction, opt Vector up) argument is not a Vector!");
        }
        else
            wi::lua::SError(L, "LookTo(Vector eye, Vector direction, opt Vector up) not enough arguments!");
        return 1;
    }

    int Matrix::LookAt(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Vector* pos = Luna<Vector>::lightcheck(L, 1);
            Vector* dir = Luna<Vector>::lightcheck(L, 2);
            if (dir != nullptr)
            {
                XMVECTOR Up;
                if (argc > 3)
                {
                    Vector* up = Luna<Vector>::lightcheck(L, 3);
                    Up = XMLoadFloat4(up);
                }
                else
                    Up = XMVectorSet(0, 1, 0, 0);
                Luna<Matrix>::push(L, new Matrix(XMMatrixLookAtLH(XMLoadFloat4(pos), XMLoadFloat4(dir), Up)));
            }
            else
                wi::lua::SError(L, "LookAt(Vector eye, Vector focusPos, opt Vector up) argument is not a Vector!");
        }
        else
            wi::lua::SError(L, "LookAt(Vector eye, Vector focusPos, opt Vector up) not enough arguments!");
        return 1;
    }

    int Matrix::multiply(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Matrix* m1 = Luna<Matrix>::lightcheck(L, 1);
            Matrix* m2 = Luna<Matrix>::lightcheck(L, 2);
            if (m1 && m2)
            {
                Luna<Matrix>::push(L, new Matrix(XMMatrixMultiply(XMLoadFloat4x4(m1), XMLoadFloat4x4(m2))));
                return 1;
            }
        }
        wi::lua::SError(L, "multiply(Matrix m1,m2) not enough arguments!");
        return 0;
    }
    int Matrix::add(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 1)
        {
            Matrix* m1 = Luna<Matrix>::lightcheck(L, 1);
            Matrix* m2 = Luna<Matrix>::lightcheck(L, 2);
            if (m1 && m2)
            {
                Luna<Matrix>::push(L, new Matrix(XMLoadFloat4x4(m1) + XMLoadFloat4x4(m2)));
                return 1;
            }
        }
        wi::lua::SError(L, "add(Matrix m1,m2) not enough arguments!");
        return 0;
    }
    int Matrix::transpose(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 0)
        {
            Matrix* m1 = Luna<Matrix>::lightcheck(L, 1);
            if (m1)
            {
                Luna<Matrix>::push(L, new Matrix(XMMatrixTranspose(XMLoadFloat4x4(m1))));
                return 1;
            }
        }
        wi::lua::SError(L, "transpose(Matrix m) not enough arguments!");
        return 0;
    }
    int Matrix::inverse(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc > 0)
        {
            Matrix* m1 = Luna<Matrix>::lightcheck(L, 1);
            if (m1)
            {
                XMVECTOR det;
                Luna<Matrix>::push(L, new Matrix(XMMatrixInverse(&det, XMLoadFloat4x4(m1))));
                wi::lua::SSetFloat(L, XMVectorGetX(det));
                return 2;
            }
        }
        wi::lua::SError(L, "inverse(Matrix m) not enough arguments!");
        return 0;
    }


    void Matrix::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            Luna<Matrix>::Register(L, "vEngine");
        }
    }
}
