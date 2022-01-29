#if __has_include("Core/Sandbox/.build/vSandboxLua.h")
    #include "Core/Sandbox/.build/vSandboxLua.h"
#endif

#include "Core/Scripting/Lua/vLuaBooter.h"
#include "Vendors/lua_rapidjson/rapidjson.cpp"
#include "Core/Tools/wiBacklog.h"
#include "Core/Helpers/wiHelper.h"

#include "Core/Scripting/Lua/Backlog/vBacklog.h"
#include "Core/Scripting/Lua/Math/vMath.h"
#include "Core/Scripting/Lua/Color/vColor.h"
#include "Core/Scripting/Lua/Config/vConfig.h"
#include "Core/Scripting/Lua/Config/vWorld.h"
#include "Core/Scripting/Lua/wiApplication_BindLua.h"
#include "Core/Scripting/Lua/wiRenderPath_BindLua.h"
#include "Core/Scripting/Lua/wiRenderPath2D_BindLua.h"
#include "Core/Scripting/Lua/wiLoadingScreen_BindLua.h"
#include "Core/Scripting/Lua/wiRenderPath3D_BindLua.h"
#include "Core/Scripting/Lua/Texture/vTexture.h"
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
            // Binds Sandbox Functions
            Backlog::Bind(cInstance.instance);
            Vector::Bind(cInstance.instance);
            Matrix::Bind(cInstance.instance);
            Color::Bind(cInstance.instance);
            Config::Bind(cInstance.instance);
            World::Bind(cInstance.instance);
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

    void Signal(const std::string& name)
    {
        #if __has_include("Core/Sandbox/.build/vSandboxLua.h")
            const char* signalType = name.c_str();
            for (auto& i : LuaInstances)
            {
                auto& L = i.first;
                lua_getglobal(L, "onvEngineSignal");
                lua_pushstring(L, signalType);
                lua_call(L, 1, 0);
            }
        #endif
    }
    void KillProcesses()
    {
        for (auto& i : LuaInstances)
        {
            auto& L = i.first;
            RunText(L, "vEngine.thread.destroyAll()");
        }
    }
}