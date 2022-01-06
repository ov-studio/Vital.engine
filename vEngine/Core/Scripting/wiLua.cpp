#if __has_include("Core/Sandbox/wiSandboxLua.h")
    #include "Core/Sandbox/wiSandboxLua.h"
    #include "Core/Scripting/wiLua.h"
    #include "Core/Tools/wiBacklog.h"
    #include "Core/Helpers/wiHelper.h"
    #include "Core/Scripting/Lua/wiApplication_BindLua.h"
    #include "Core/Scripting/Lua/wiRenderPath_BindLua.h"
    #include "Core/Scripting/Lua/wiRenderPath2D_BindLua.h"
    #include "Core/Scripting/Lua/wiLoadingScreen_BindLua.h"
    #include "Core/Scripting/Lua/wiRenderPath3D_BindLua.h"
    #include "Core/Scripting/Lua/wiTexture_BindLua.h"
    #include "Core/Scripting/Lua/wiRenderer_BindLua.h"
    #include "Core/Scripting/Lua/wiAudio_BindLua.h"
    #include "Core/Scripting/Lua/wiSprite_BindLua.h"
    #include "Core/Scripting/Lua/wiImageParams_BindLua.h"
    #include "Core/Scripting/Lua/wiSpriteAnim_BindLua.h"
    #include "Core/Scripting/Lua/wiScene_BindLua.h"
    #include "Core/Scripting/Lua/wiMath_BindLua.h"
    #include "Core/Scripting/Lua/wiInput_BindLua.h"
    #include "Core/Scripting/Lua/wiSpriteFont_BindLua.h"
    #include "Core/Scripting/Lua/wiBacklog_BindLua.h"
    #include "Core/Scripting/Lua/wiNetwork_BindLua.h"
    #include "Core/Scripting/Lua/wiPrimitive_BindLua.h"
    #include "Core/Helpers/wiTimer.h"
    #include "Core/Helpers/wiVector.h"

    #include <memory>

    namespace wi::lua
    {
        // Definitions
        struct LuaInternal
        {
            lua_State* m_luaState = NULL;
            int m_status = 0; //last call status
            ~LuaInternal()
            {
                if (m_luaState != NULL)
                {
                    lua_close(m_luaState);
                }
            }
        };
        static const char* WILUA_ERROR_PREFIX = "[Lua Error] ";
        static const luaL_Reg WILUA_LIBS[] = {
            { "_G", luaopen_base },
            { LUA_TABLIBNAME, luaopen_table },
            { LUA_STRLIBNAME, luaopen_string },
            { LUA_MATHLIBNAME, luaopen_math },
            { LUA_DBLIBNAME, luaopen_debug },
            { LUA_COLIBNAME, luaopen_coroutine },
            { LUA_UTF8LIBNAME, luaopen_utf8 },
            //{ "json", luaopen_rapidjson },
            { NULL, NULL }
        };

        // Variables
        LuaInternal luainternal;
        std::string script_path;

        lua_State* createInstance()
        {
            lua_State* cInstance = luaL_newstate();
            // Loads whitelisted libraries
            const luaL_Reg* lib = WILUA_LIBS;
            for (; lib->func; lib++)
            {
                luaL_requiref(cInstance, lib->name, lib->func, 1);
                lua_pop(cInstance, 1);
            }
            // Loads whitelisted scripts
            for (int i = 0; i < sandbox::lua::modules.size(); ++i)
            {
                if (sandbox::lua::modules[i].moduleName != "Server") {
                    for (int j = 0; j < sandbox::lua::modules[i].moduleScripts.size(); ++j)
                    {
                        RunText(cInstance, sandbox::lua::modules[i].moduleScripts[j]);
                    }
                }
            }
            // Loads engine bindings
            /*
            Application_BindLua::Bind();
            Canvas_BindLua::Bind();
            RenderPath_BindLua::Bind();
            RenderPath2D_BindLua::Bind();
            LoadingScreen_BindLua::Bind();
            RenderPath3D_BindLua::Bind();
            Texture_BindLua::Bind();
            renderer::Bind();
            Audio_BindLua::Bind();
            Sprite_BindLua::Bind();
            ImageParams_BindLua::Bind();
            SpriteAnim_BindLua::Bind();
            scene::Bind();
            Vector_BindLua::Bind();
            Matrix_BindLua::Bind();
            Input_BindLua::Bind();
            SpriteFont_BindLua::Bind();
            backlog::Bind();
            Network_BindLua::Bind();
            primitive::Bind();
            */
            return cInstance;
        }

        void Initialize()
        {
            wi::Timer timer;
            luainternal.m_luaState = createInstance();
            wi::backlog::post("wi::lua Initialized (" + std::to_string((int)std::round(timer.elapsed())) + " ms)");
        }

        lua_State* GetLuaState()
        {
            return luainternal.m_luaState;
        }

        // TODO: NEEDS IMPROVEMENT..
        bool Success(lua_State* L)
        {
            return luainternal.m_status == 0;
        }
        bool Failed(lua_State* L)
        {
            return luainternal.m_status != 0;
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
            script_path = wi::helper::GetDirectoryFromPath(filename);
            wi::vector<uint8_t> filedata;
            if (wi::helper::FileRead(filename, filedata))
            {
                return RunText(L, std::string(filedata.begin(), filedata.end()));
            }
            return false;
        }
        bool RunText(lua_State* L, const std::string& script)
        {
            luainternal.m_status = luaL_loadstring(L, script.c_str());
            if (Success(L))
            {
                luainternal.m_status = lua_pcall(L, 0, LUA_MULTRET, 0);
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
        void RegisterLibrary(lua_State* L, const std::string& tableName, const luaL_Reg* functions)
        {
            if (luaL_newmetatable(luainternal.m_luaState, tableName.c_str()) != 0)
            {
                //table is not yet present
                lua_pushvalue(L, -1);
                lua_setfield(L, -2, "__index"); // Object.__index = Object
                AddFuncArray(L, functions);
            }
        }
        bool RegisterObject(lua_State* L, const std::string& tableName, const std::string& name, void* object)
        {
            RegisterLibrary(L, tableName, nullptr);
            // does this call need to be checked? eg. userData == nullptr?
            void** userData = static_cast<void**>(lua_newuserdata(L, sizeof(void*)));
            *(userData) = object;
            luaL_setmetatable(L, tableName.c_str());
            lua_setglobal(L, name.c_str());
            return true;
        }
        void AddFunc(lua_State* L, const std::string& name, lua_CFunction function)
        {
            lua_pushcfunction(L, function);
            lua_setfield(L, -2, name.c_str());
        }
        void AddFuncArray(lua_State* L, const luaL_Reg* functions)
        {
            if (functions != nullptr)
            {
                luaL_setfuncs(L, functions, 0);
            }
        }
        void AddInt(lua_State* L, const std::string& name, int data)
        {
            lua_pushinteger(L, data);
            lua_setfield(L, -2, name.c_str());
        }
        const std::string& GetScriptPath()
        {
            return script_path;
        }

        inline void SignalHelper(lua_State* L, const char* str)
        {
            lua_getglobal(L, "onvEngineSignal");
            lua_pushstring(L, str);
            lua_call(L, 1, 0);
        }
        void FixedUpdate()
        {
            SignalHelper(luainternal.m_luaState, "vEngine_onAsyncUpdate");
        }
        void Update()
        {
            SignalHelper(luainternal.m_luaState, "vEngine_onUpdate");
        }
        void Render()
        {
            SignalHelper(luainternal.m_luaState, "vEngine_onRender");
        }
        void Signal(const std::string& name)
        {
            SignalHelper(luainternal.m_luaState, name.c_str());
        }
        void KillProcesses()
        {
            RunText(luainternal.m_luaState ,"vEngine.thread.destroyAll()");
        }

        std::string SGetString(lua_State* L, int stackpos)
        {
            const char* str = lua_tostring(L, stackpos);
            if (str != nullptr)
                return str;
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
#endif