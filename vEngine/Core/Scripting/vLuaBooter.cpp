#if __has_include("Core/Sandbox/.build/vSandboxLua.h")
    #include "Core/Sandbox/.build/vSandboxLua.h"
#endif

#include "Core/Scripting/vLuaBooter.h"
#include "Vendors/lua_rapidjson/rapidjson.cpp"
#include "Core/Tools/wiBacklog.h"
#include "Core/Helpers/wiHelper.h"

#include "Core/Scripting/Lua/Backlog/vBacklog.h"
#include "Core/Scripting/Lua/Math/vMath.h"
#include "Core/Scripting/Lua/wiApplication_BindLua.h"
#include "Core/Scripting/Lua/wiRenderPath_BindLua.h"
#include "Core/Scripting/Lua/wiRenderPath2D_BindLua.h"
#include "Core/Scripting/Lua/wiLoadingScreen_BindLua.h"
#include "Core/Scripting/Lua/wiRenderPath3D_BindLua.h"
#include "Core/Scripting/Lua/Texture/vTexture.h"
#include "Core/Scripting/Lua/Game/vGame.h"
#include "Core/Scripting/Lua/wiAudio_BindLua.h"
#include "Core/Scripting/Lua/wiSprite_BindLua.h"
#include "Core/Scripting/Lua/wiImageParams_BindLua.h"
#include "Core/Scripting/Lua/wiSpriteAnim_BindLua.h"
#include "Core/Scripting/Lua/wiScene_BindLua.h"
#include "Core/Scripting/Lua/wiInput_BindLua.h"
#include "Core/Scripting/Lua/wiSpriteFont_BindLua.h"
#include "Core/Scripting/Lua/wiNetwork_BindLua.h"
#include "Core/Scripting/Lua/wiPrimitive_BindLua.h"
#include "Core/Helpers/wiTimer.h"
#include "Core/Helpers/wiVector.h"

#include <memory>

namespace wi::lua
{
    // Definitions
    lua_CInstance internalInstance;
    lua_CInstancePool LuaInstances = {};
    static const char* WILUA_ERROR_PREFIX = "[Lua Error] ";
    static const luaL_Reg whitelisted_libs[] = {
        { "_G", luaopen_base },
        { LUA_TABLIBNAME, luaopen_table },
        { LUA_STRLIBNAME, luaopen_string },
        { LUA_MATHLIBNAME, luaopen_math },
        { LUA_DBLIBNAME, luaopen_debug },
        { LUA_COLIBNAME, luaopen_coroutine },
        { LUA_UTF8LIBNAME, luaopen_utf8 },
        { "json", luaopen_rapidjson },
        { NULL, NULL }
    };
    static const char* blacklisted_globals[] = {"dofile", "load", "loadfile"};

        // Creates & Destroys instances
    lua_State* createInstance()
    {
        lua_CInstance cInstance;
        cInstance.instance = luaL_newstate();
        const luaL_Reg* library;
        for (library = whitelisted_libs; library->func; library++) {
            luaL_requiref(cInstance.instance, library->name, library->func, 1);
            lua_pop(cInstance.instance, 1);
        }
        // Unloads blacklisted globals
        for (auto globalName : blacklisted_globals)
        {
            SSetNull(cInstance.instance);
            lua_setglobal(cInstance.instance, globalName);
        }
        #if __has_include("Core/Sandbox/.build/vSandboxLua.h")
            // Loads whitelisted scripts
            RunText(cInstance.instance, R"(
                vEngine = {}
                vEngine.math = math; math = nil;
                vEngine.string = string; string = nil;
                vEngine.json = json; json = nil;
            )");
            for (int i = 0; i < sandbox::lua::modules.size(); ++i)
            {
                if (sandbox::lua::modules[i].moduleName != "Server") {
                    for (int j = 0; j < sandbox::lua::modules[i].moduleScripts.size(); ++j)
                    {
                        RunText(cInstance.instance, sandbox::lua::modules[i].moduleScripts[j]);
                    }
                }
            }
            // Loads engine bindings
            Backlog::Bind(cInstance.instance);
            Vector::Bind(cInstance.instance);
            Matrix::Bind(cInstance.instance);
            Game::Bind(cInstance.instance);
            Application_BindLua::Bind(cInstance.instance);
            Canvas_BindLua::Bind(cInstance.instance);
            RenderPath_BindLua::Bind(cInstance.instance);
            RenderPath2D_BindLua::Bind(cInstance.instance);
            LoadingScreen_BindLua::Bind(cInstance.instance);
            RenderPath3D_BindLua::Bind(cInstance.instance);
            Texture::Bind(cInstance.instance);
            Audio_BindLua::Bind(cInstance.instance);
            Sprite_BindLua::Bind(cInstance.instance);
            ImageParams_BindLua::Bind(cInstance.instance);
            SpriteAnim_BindLua::Bind(cInstance.instance);
            scene::Bind(cInstance.instance);
            Input_BindLua::Bind(cInstance.instance);
            SpriteFont_BindLua::Bind(cInstance.instance);
            Network_BindLua::Bind(cInstance.instance);
            primitive::Bind(cInstance.instance);
            // Cache created instance
            LuaInstances[(cInstance.instance)] = cInstance;
        #endif
        return cInstance.instance;
    }
    void destroyInstance(lua_State* cInstance)
    {
        LuaInstances.erase(cInstance);
        lua_close(cInstance);
    }

    lua_State* GetInternalInstance()
    {
        return internalInstance.instance;
    }
    lua_CInstancePool GetInstancePool()
    {
        return LuaInstances;
    }

    void Initialize()
    {
        wi::Timer timer;
        internalInstance = LuaInstances[(createInstance())];
        wi::backlog::post("wi::lua Initialized (" + std::to_string((int)std::round(timer.elapsed())) + " ms)");
    }

    bool Success(lua_State* L)
    {
        return LuaInstances[L].execStatus == 0;
    }
    bool Failed(lua_State* L)
    {
        return LuaInstances[L].execStatus != 0;
    }
    std::string GetErrorMsg(lua_State* L)
    {
        if (Failed(L)) {
            std::string retVal = lua_tostring(L, -1);
            return retVal;
        }
        return std::string("");
    }
    std::string PopErrorMsg(lua_State* L)
    {
        std::string retVal = lua_tostring(L, -1);
        lua_pop(L, 1); // remove error message
        return retVal;
    }

    void PostErrorMsg(lua_State* L)
    {
        if (Failed(L))
        {
            const char* str = lua_tostring(L, -1);
            if (str == nullptr)
                return;
            std::string ss;
            ss += WILUA_ERROR_PREFIX;
            ss += str;
            wi::backlog::post(ss, wi::backlog::LogLevel::Error);
            lua_pop(L, 1); // remove error message
        }
    }
    bool RunFile(lua_State* L, const std::string& filename)
    {
        wi::vector<uint8_t> filedata;
        if (wi::helper::FileRead(filename, filedata))
        {
            return RunText(L, std::string(filedata.begin(), filedata.end()));
        }
        return false;
    }
    bool RunText(lua_State* L, const std::string& script)
    {
        LuaInstances[L].execStatus = luaL_loadstring(L, script.c_str());
        if (Success(L))
        {
            LuaInstances[L].execStatus = lua_pcall(L, 0, LUA_MULTRET, 0);
            if (Success(L))
                return true;
        }
        PostErrorMsg(L);
        return false;
    }
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
                lua_pushvalue(L, -1);
                lua_setfield(L, -2, index.c_str());
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

    inline void SignalHelper(const char* signalType)
    {
        #if __has_include("Core/Sandbox/.build/vSandboxLua.h")
            for (auto& i : LuaInstances)
            {
                auto& L = i.first;
                lua_getglobal(L, "onvEngineSignal");
                lua_pushstring(L, signalType);
                lua_call(L, 1, 0);
            }
        #endif
    }
    void Signal(const std::string& name)
    {
        SignalHelper(name.c_str());
    }
    void KillProcesses()
    {
        for (auto& i : LuaInstances)
        {
            auto& L = i.first;
            RunText(L, "vEngine.thread.destroyAll()");
        }
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
        ss += WILUA_ERROR_PREFIX;
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