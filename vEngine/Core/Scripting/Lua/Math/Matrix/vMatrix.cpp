#include "Core/Scripting/Lua/Math/vMath.h"

namespace wi::lua
{
    // Library Binder
    const char Matrix::libraryName[] = "matrix";
    const luaL_Reg Matrix::libraryFunctions[] = {
        { "translation", translation },
        { "rotation", rotation },
        { "rotationX", rotationX },
        { "rotationY", rotationY },
        { "rotationZ", rotationZ },
        { "quatRotation", quatRotation },
        { "scaling", scaling },
        { "lookTo", lookTo },
        { "lookAt", lookAt },
        { NULL, NULL }
    };

    // Class Binder
    const char Matrix::className[] = "create";
    Luna<Matrix>::FunctionType Matrix::methods[] = {
        lunamethod(Matrix, getRow),
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
        Vector* cVector1 = Luna<Vector>::lightcheck(L, 1);
        Vector* cVector2 = Luna<Vector>::lightcheck(L, 2);
        Vector* cVector3 = Luna<Vector>::lightcheck(L, 3);
        Vector* cVector4 = Luna<Vector>::lightcheck(L, 4);
        if (cVector1)
        {
            this->m[0][0] = cVector1->x;
            this->m[0][1] = cVector1->y;
            this->m[0][2] = cVector1->z;
            this->m[0][3] = cVector1->w;
        }
        if (cVector2)
        {
            this->m[1][0] = cVector2->x;
            this->m[1][1] = cVector2->y;
            this->m[1][2] = cVector2->z;
            this->m[1][3] = cVector2->w;
        }
        if (cVector3)
        {
            this->m[2][0] = cVector3->x;
            this->m[2][1] = cVector3->y;
            this->m[2][2] = cVector3->z;
            this->m[2][3] = cVector3->w;
        }
        if (cVector4)
        {
            this->m[3][0] = cVector4->x;
            this->m[3][1] = cVector4->y;
            this->m[3][2] = cVector4->z;
            this->m[3][3] = cVector4->w;
        }
    }

    // Instance Binder
    void Matrix::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            RegisterLibrary(L, Matrix::libraryName, Matrix::libraryFunctions, "vEngine", {"math"});
            Luna<Matrix>::Register(L, "vEngine", {"math", Matrix::libraryName});
        }
    }

    // Library Methods
    int Matrix::translation(lua_State* L)
    {
        XMMATRIX cMatrix = XMMatrixIdentity();
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
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
    int Matrix::rotation(lua_State* L)
    {
        XMMATRIX cMatrix = XMMatrixIdentity();
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
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
    int Matrix::rotationX(lua_State* L)
    {
        XMMATRIX cMatrix = XMMatrixIdentity();
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
        {
            cMatrix = XMMatrixRotationX(wi::lua::SGetFloat(L, 1));
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }
    int Matrix::rotationY(lua_State* L)
    {
        XMMATRIX cMatrix = XMMatrixIdentity();
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
        {
            cMatrix = XMMatrixRotationY(wi::lua::SGetFloat(L, 1));
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }
    int Matrix::rotationZ(lua_State* L)
    {
        XMMATRIX cMatrix = XMMatrixIdentity();
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
        {
            cMatrix = XMMatrixRotationZ(wi::lua::SGetFloat(L, 1));
        }
        Luna<Matrix>::push(L, new Matrix(cMatrix));
        return 1;
    }
    int Matrix::quatRotation(lua_State* L)
    {
        XMMATRIX cMatrix = XMMatrixIdentity();
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
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
    int Matrix::scaling(lua_State* L)
    {
        XMMATRIX cMatrix = XMMatrixIdentity();
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
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
    // TODO: WIP//
    int Matrix::lookTo(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount > 1)
        {
            Vector* pos = Luna<Vector>::lightcheck(L, 1);
            Vector* dir = Luna<Vector>::lightcheck(L, 2);
            if (pos != nullptr && dir != nullptr)
            {
                XMVECTOR Up;
                if (argCount > 3)
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
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount > 1)
        {
            Vector* pos = Luna<Vector>::lightcheck(L, 1);
            Vector* dir = Luna<Vector>::lightcheck(L, 2);
            if (dir != nullptr)
            {
                XMVECTOR Up;
                if (argCount > 3)
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
    // TODO: ^^ END HERE

    // Class Methods
    int Matrix::getRow(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        int row = 0;
        if (argCount >= 1)
        {
            row = wi::lua::SGetInt(L, 1);
            if (row < 0 || row > 3)
                row = 0;
        }
        XMFLOAT4 matrixRow = XMFLOAT4(m[row][0], m[row][1], m[row][2], m[row][3]);
        Luna<Vector>::push(L, new Vector(matrixRow));
        return 1;
    }
    int Matrix::multiply(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
        {
            Matrix* cMatrix = Luna<Matrix>::lightcheck(L, 1);
            if (cMatrix)
            {
                Luna<Matrix>::push(L, new Matrix(XMMatrixMultiply(XMLoadFloat4x4(this), XMLoadFloat4x4(cMatrix))));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: matrix:multiply(userdata matrix)");
        return 0;
    }
    int Matrix::add(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
        {
            Matrix* cMatrix = Luna<Matrix>::lightcheck(L, 1);
            if (cMatrix)
            {
                Luna<Matrix>::push(L, new Matrix(XMLoadFloat4x4(this) + XMLoadFloat4x4(cMatrix)));
                return 1;
            }
        }
        wi::lua::SError(L, "Syntax: matrix:add(userdata matrix)");
        return 0;
    }
    int Matrix::transpose(lua_State* L)
    {
        Luna<Matrix>::push(L, new Matrix(XMMatrixTranspose(XMLoadFloat4x4(this))));
        return 1;
    }
    int Matrix::inverse(lua_State* L)
    {
        XMVECTOR det;
        Luna<Matrix>::push(L, new Matrix(XMMatrixInverse(&det, XMLoadFloat4x4(this))));
        wi::lua::SSetFloat(L, XMVectorGetX(det));
        return 1;
    }
}
