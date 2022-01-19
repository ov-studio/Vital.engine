#include "Core/Scripting/Lua/vLua.h"
#include "Core/Tools/wiBacklog.h"

namespace wi::lua
{
    bool RegisterFunc(lua_State* L, const std::string& name, lua_CFunction function)
    {
        lua_register(L, name.c_str(), function);
        PostErrorMsg(L);
        return Success(L);
    }
    void RegisterNamespace(lua_State* L, const char *namespac, const wi::vector<std::string>& namespaceIndex)
    {
        if (namespac && strlen(namespac))
        {
            lua_getglobal(L, namespac);
            if (lua_isnil(L, -1))
            {
                // Namespace doesn't exist, create it
                lua_newtable(L);
                lua_pushvalue(L, -1); // Duplicate table pointer since setglobal pops the value
                lua_setglobal(L, namespac);
            }
            // Create Indexes
            for (auto& index : namespaceIndex)
            {
                lua_getfield(L, -1, index.c_str());
                if (lua_isnil(L, -1))
                {
                    lua_pop(L, 1);
                    lua_pushvalue(L, -1);
                    lua_setfield(L, -2, index.c_str());
                }
                lua_remove(L, -2);
            }
        }
    }
    void RegisterLibrary(lua_State* L, const std::string& tableName, const luaL_Reg* functions, const char *namespac, const wi::vector<std::string>& namespaceIndex)
    {
        if (namespac && strlen(namespac))
        {
            RegisterNamespace(L, namespac, namespaceIndex);
            // Create our main table
            lua_pushvalue(L, -1);
            lua_setfield(L, -2, tableName.c_str());
            lua_remove(L, -2);
            AddFuncs(L, functions);
        }
        else
        {
            lua_getglobal(L, tableName.c_str());
            if (lua_isnil(L, -1))
            {
                // Table doesn't exist, create it
                lua_newtable(L);
                lua_pushvalue(L, -1); // Duplicate table pointer since setglobal pops the value
                lua_setglobal(L, tableName.c_str());
            }
            AddFuncs(L, functions);
        }
    }
    bool RegisterObject(lua_State* L, const std::string& tableName, void* object, const char *namespac, const wi::vector<std::string>& namespaceIndex)
    {
        RegisterLibrary(L, tableName, nullptr, namespac, namespaceIndex);
        void** userData = static_cast<void**>(lua_newuserdata(L, sizeof(void*)));
        *(userData) = object;
        luaL_setmetatable(L, tableName.c_str());
        return true;
    }
    void AddFunc(lua_State* L, const std::string& name, lua_CFunction function)
    {
        if (function)
        {
            lua_pushcfunction(L, function);
            lua_setfield(L, -2, name.c_str());
        }
    }
    void AddFuncs(lua_State* L, const luaL_Reg* functions)
    {
        if (functions)
        {
            luaL_setfuncs(L, functions, 0);
        }
    }
    void AddInt(lua_State* L, const std::string& name, int data)
    {
        lua_pushinteger(L, data);
        lua_setfield(L, -2, name.c_str());
    }

    std::string SGetString(lua_State* L, int stackpos)
    {
        const char* str = lua_tostring(L, stackpos);
        if (str != nullptr) return str;
        return std::string("");
    }
    bool SIsString(lua_State* L, int stackpos)
    {
        return lua_isstring(L, stackpos) != 0;
    }
    bool SIsNumber(lua_State* L, int stackpos)
    {
        return lua_isnumber(L, stackpos) != 0;
    }
    int SGetInt(lua_State* L, int stackpos)
    {
        return static_cast<int>(SGetLongLong(L, stackpos));
    }
    long SGetLong(lua_State* L, int stackpos)
    {
        return static_cast<long>(SGetLongLong(L, stackpos));
    }
    long long SGetLongLong(lua_State* L, int stackpos)
    {
        return lua_tointeger(L, stackpos);
    }
    float SGetFloat(lua_State* L, int stackpos)
    {
        return static_cast<float>(SGetDouble(L, stackpos));
    }
    XMFLOAT2 SGetFloat2(lua_State* L, int stackpos)
    {
        return XMFLOAT2(SGetFloat(L, stackpos), SGetFloat(L, stackpos + 1));
    }
    XMFLOAT3 SGetFloat3(lua_State* L, int stackpos)
    {
        return XMFLOAT3(SGetFloat(L, stackpos), SGetFloat(L, stackpos + 1), SGetFloat(L, stackpos + 2));
    }
    XMFLOAT4 SGetFloat4(lua_State* L, int stackpos)
    {
        return XMFLOAT4(SGetFloat(L, stackpos), SGetFloat(L, stackpos + 1), SGetFloat(L, stackpos + 2), SGetFloat(L, stackpos + 3));
    }
    double SGetDouble(lua_State* L, int stackpos)
    {
        return lua_tonumber(L, stackpos);
    }
    bool SGetBool(lua_State* L, int stackpos)
    {
        return lua_toboolean(L, stackpos) != 0;
    }
    int SGetArgCount(lua_State* L)
    {
        return lua_gettop(L);
    }
    void* SGetUserData(lua_State* L)
    {
        return lua_touserdata(L, 1);
    }

    void SSetInt(lua_State* L, int data)
    {
        lua_pushinteger(L, (lua_Integer)data);
    }
    void SSetLong(lua_State* L, long data)
    {
        lua_pushinteger(L, (lua_Integer)data);
    }
    void SSetLongLong(lua_State* L, long long data)
    {
        lua_pushinteger(L, (lua_Integer)data);
    }
    void SSetFloat(lua_State* L, float data)
    {
        lua_pushnumber(L, (lua_Number)data);
    }
    void SSetFloat2(lua_State* L, const XMFLOAT2& data)
    {
        SSetFloat(L, data.x);
        SSetFloat(L, data.y);
    }
    void SSetFloat3(lua_State* L, const XMFLOAT3& data)
    {
        SSetFloat(L, data.x);
        SSetFloat(L, data.y);
        SSetFloat(L, data.z);
    }
    void SSetFloat4(lua_State* L, const XMFLOAT4& data)
    {
        SSetFloat(L, data.x);
        SSetFloat(L, data.y);
        SSetFloat(L, data.z);
        SSetFloat(L, data.w);
    }
    void SSetDouble(lua_State* L, double data)
    {
        lua_pushnumber(L, (lua_Number)data);
    }
    void SSetString(lua_State* L, const std::string& data)
    {
        lua_pushstring(L, data.c_str());
    }
    void SSetBool(lua_State* L, bool data)
    {
        lua_pushboolean(L, static_cast<int>(data));
    }
    void SSetPointer(lua_State* L, void* data)
    {
        lua_pushlightuserdata(L, data);
    }
    void SSetNull(lua_State* L)
    {
        lua_pushnil(L);
    }

    void SError(lua_State* L, const std::string& error)
    {
        //retrieve line number for error info
        lua_Debug ar;
        lua_getstack(L, 1, &ar);
        lua_getinfo(L, "nSl", &ar);
        int line = ar.currentline;

        std::string ss;
        ss += "Line " + std::to_string(line) + ": ";
        if (!error.empty())
        {
            ss += error;
        }
        wi::backlog::post(ss);
    }
    void SAddMetatable(lua_State* L, const std::string& name)
    {
        luaL_newmetatable(L, name.c_str());
    }
}