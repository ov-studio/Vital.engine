#include "Core/Scripting/Lua/wiTexture_BindLua.h"

using namespace wi::graphics;

namespace wi::lua
{

	const char Texture_BindLua::className[] = "texture";

	Luna<Texture_BindLua>::FunctionType Texture_BindLua::methods[] = {
		{ NULL, NULL }
	};
	Luna<Texture_BindLua>::PropertyType Texture_BindLua::properties[] = {
		{ NULL, NULL }
	};

	Texture_BindLua::Texture_BindLua(Texture texture) :texture(texture)
	{
	}
	Texture_BindLua::Texture_BindLua(lua_State* L)
	{
	}

	void Texture_BindLua::Bind(lua_State* L)
	{
		static bool initialized = false;
		if (!initialized)
		{
			Luna<Texture_BindLua>::Register(L, "vEngine");
			initialized = true;
		}
	}

}
