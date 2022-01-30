#include "Core/Scripting/Lua/Common/vGame.h"
#include "Core/Scripting/Lua/Config/vConfig.h"

namespace wi::lua
{
    // Library Binder
    const char Config::libraryName[] = "config";
    const luaL_Reg Config::libraryFunctions[] = {
        { "setGameSpeed", setGameSpeed },
        { "getGameSpeed", getGameSpeed },
        { "setShadowProps2D", setShadowProps2D },
        { "setShadowPropsCube", setShadowPropsCube },
        { "setVSyncEnabled", setVSyncEnabled },
        { "setOcclusionCullingEnabled", setOcclusionCullingEnabled },
        { "reloadShaders", reloadShaders },
        { NULL, NULL }
    };

    // Instance Binder
    void Config::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            RegisterLibrary(L, Config::libraryName, Config::libraryFunctions, "vEngine");
        }
    }

    // Library Methods
    int Config::setGameSpeed(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
        {
            wi::renderer::SetGameSpeed(wi::lua::SGetFloat(L, 1));
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vEngine.config.setGameSpeed(float speed)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
    int Config::getGameSpeed(lua_State* L)
    {
        wi::lua::SSetFloat(L, wi::renderer::GetGameSpeed());
        wi::lua::SSetBool(L, true);
        return 1;
    }
    int Config::setShadowProps2D(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 2)
        {
            wi::renderer::SetShadowProps2D(wi::lua::SGetInt(L, 1), wi::lua::SGetInt(L, 2));
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vEngine.config.setShadowProps2D(int resolution, int count)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
    int Config::setShadowPropsCube(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 2)
        {
            wi::renderer::SetShadowPropsCube(wi::lua::SGetInt(L, 1), wi::lua::SGetInt(L, 2));
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vEngine.config.setShadowPropsCube(int resolution, int count)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
    int Config::setVSyncEnabled(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
        {
            wi::eventhandler::SetVSync(wi::lua::SGetBool(L, 1));
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vEngine.config.setVSyncEnabled(bool state)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
    int Config::setOcclusionCullingEnabled(lua_State* L)
    {
        int argCount = wi::lua::SGetArgCount(L);
        if (argCount >= 1)
        {
            wi::renderer::SetOcclusionCullingEnabled(wi::lua::SGetBool(L, 1));
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vEngine.config.setOcclusionCullingEnabled(bool state)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
    int Config::reloadShaders(lua_State* L)
    {
        wi::renderer::ReloadShaders();
        wi::lua::SSetBool(L, true);
        return 1;
    }
};
