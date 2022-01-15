#pragma once
#include "Core/Scripting/vLuaBooter.h"
#include "Core/Interfaces/wiLoadingScreen.h"
#include "Core/Scripting/Lua/wiRenderPath2D_BindLua.h"

namespace wi::lua
{

	class LoadingScreen_BindLua : public RenderPath2D_BindLua
	{
	private:
		LoadingScreen loadingscreen;
	public:
		static const char className[];
		static Luna<LoadingScreen_BindLua>::FunctionType methods[];
		static Luna<LoadingScreen_BindLua>::PropertyType properties[];

		LoadingScreen_BindLua(LoadingScreen* component)
		{
			this->component = component;
		}
		LoadingScreen_BindLua(lua_State* L)
		{
			this->component = &loadingscreen;
		}

		int AddLoadingTask(lua_State* L);
		int OnFinished(lua_State* L);

		static void Bind(lua_State* L);
	};

}
