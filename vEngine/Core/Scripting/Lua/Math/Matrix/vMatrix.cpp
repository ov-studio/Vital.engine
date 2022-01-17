#include "Core/Scripting/Lua/Math/vMath.h"

namespace wi::lua
{
    // Class Binder
    const char Matrix::className[] = "matrix";
    Luna<Matrix>::FunctionType Matrix::methods[] = {
        lunamethod(Matrix, getRow),
        lunamethod(Matrix, translate),
        lunamethod(Matrix, rotate),
        lunamethod(Matrix, rotateX),
        lunamethod(Matrix, rotateY),
        lunamethod(Matrix, rotateZ),
        lunamethod(Matrix, quatRotate),
        lunamethod(Matrix, scale),
        lunamethod(Matrix, lookTo),
        lunamethod(Matrix, lookAt),
        lunamethod(Matrix, add),
        lunamethod(Matrix, multiply),
        lunamethod(Matrix, transpose),
        lunamethod(Matrix, inverse),
        { NULL, NULL }
    };
    Luna<Matrix>::PropertyType Matrix::properties[] = {
        { NULL, NULL }
    };
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
    void Matrix::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            Luna<Matrix>::Register(L, "vEngine");
        }
    }

    // Class Methods
    int Matrix::getRow(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        int row = 0;
        if (argc >= 1)
        {
            row = wi::lua::SGetInt(L, 1);
            if (row < 0 || row > 3)
                row = 0;
        }
        XMFLOAT4 matrixRow = XMFLOAT4(m[row][0], m[row][1], m[row][2], m[row][3]);
        Luna<Vector>::push(L, new Vector(matrixRow));
        return 1;
    }
    int Matrix::translate(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX cMatrix = XMMatrixIdentity();
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                cMatrix = XMMatrixTranslationFromVector(XMLoadFloat4(cVector));
            }
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }
    int Matrix::rotate(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX cMatrix = XMMatrixIdentity();
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                cMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat4(cVector));
            }
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }
    int Matrix::rotateX(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX cMatrix = XMMatrixIdentity();
        if (argc >= 1)
        {
            cMatrix = XMMatrixRotationX(wi::lua::SGetFloat(L, 1));
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }
    int Matrix::rotateY(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX cMatrix = XMMatrixIdentity();
        if (argc >= 1)
        {
            cMatrix = XMMatrixRotationY(wi::lua::SGetFloat(L, 1));
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }
    int Matrix::rotateZ(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX cMatrix = XMMatrixIdentity();
        if (argc >= 1)
        {
            cMatrix = XMMatrixRotationZ(wi::lua::SGetFloat(L, 1));
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }
    int Matrix::quatRotate(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX cMatrix = XMMatrixIdentity();
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                cMatrix = XMMatrixRotationQuaternion(XMLoadFloat4(cVector));
            }
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }

    int Matrix::scale(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        XMMATRIX cMatrix = XMMatrixIdentity();
        if (argc >= 1)
        {
            Vector* cVector = Luna<Vector>::lightcheck(L, 1);
            if (cVector)
            {
                cMatrix = XMMatrixScalingFromVector(XMLoadFloat4(cVector));
            }
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }

    int Matrix::lookTo(lua_State* L)
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
                wi::lua::SError(L, "lookTo(Vector eye, Vector direction, opt Vector up) argument is not a Vector!");
        }
        else
            wi::lua::SError(L, "lookTo(Vector eye, Vector direction, opt Vector up) not enough arguments!");
        return 1;
    }

    int Matrix::lookAt(lua_State* L)
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
                wi::lua::SError(L, "lookAt(Vector eye, Vector focusPos, opt Vector up) argument is not a Vector!");
        }
        else
            wi::lua::SError(L, "lookAt(Vector eye, Vector focusPos, opt Vector up) not enough arguments!");
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
}
