#include "Core/Scripting/Lua/wiNetwork_BindLua.h"
#include "Core/Network/wiNetwork.h"
#include "Core/Helpers/wiHelper.h"

namespace wi::lua
{

	const char Network_BindLua::className[] = "network";

	Luna<Network_BindLua>::FunctionType Network_BindLua::methods[] = {
		{ NULL, NULL }
	};
	Luna<Network_BindLua>::PropertyType Network_BindLua::properties[] = {
		{ NULL, NULL }
	};

	void Network_BindLua::Bind(lua_State* L)
	{
		static bool initialized = false;
		if (!initialized)
		{
			initialized = true;
			Luna<Network_BindLua>::Register(wi::lua::GetLuaState(), "vEngine");

			wi::lua::RunText(wi::lua::GetLuaState(), "network = Network()");
		}
	}

}
