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
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::renderer::SetGameSpeed(wi::lua::SGetFloat(L, 1));
            return 1;
		}
		wi::lua::SError(L,"setGameSpeed(float) not enough arguments!");
        wi::lua::SSetBool(L, false);
		return 0;
	}
	int Config::getGameSpeed(lua_State* L)
	{
		wi::lua::SSetFloat(L, wi::renderer::GetGameSpeed());
		return 1;
	}
	int Config::setShadowProps2D(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 1)
		{
			wi::renderer::SetShadowProps2D(wi::lua::SGetInt(L, 1), wi::lua::SGetInt(L, 2));
            return 1;
		}
		wi::lua::SError(L, "setShadowProps2D(int resolution, int count) not enough arguments!");
        wi::lua::SSetBool(L, false);
		return 0;
	}
	int Config::setShadowPropsCube(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 1)
		{
			wi::renderer::SetShadowPropsCube(wi::lua::SGetInt(L, 1), wi::lua::SGetInt(L, 2));
            return 1;
		}
		wi::lua::SError(L, "setShadowPropsCube(int resolution, int count) not enough arguments!");
        wi::lua::SSetBool(L, false);
		return 0;
	}
	int Config::setVSyncEnabled(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::eventhandler::SetVSync(wi::lua::SGetBool(L, 1));
            return 1;
		}
        wi::lua::SSetBool(L, false);
		return 0;
	}
	int Config::setOcclusionCullingEnabled(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
        {
			wi::renderer::SetOcclusionCullingEnabled(wi::lua::SGetBool(L, 1));
            return 1;
        }
		wi::lua::SError(L, "setOcclusionCullingEnabled(bool enabled) not enough arguments!");
        wi::lua::SSetBool(L, false);
		return 0;
	}
};
