#pragma once
#include "Core/Scripting/vLuaBooter.h"
#include "Core/Interfaces/wiRenderPath.h"

namespace wi::lua
{
	class RenderPath_BindLua
	{
	public:
		RenderPath* component = nullptr;
		static const char className[];
		static Luna<RenderPath_BindLua>::FunctionType methods[];
		static Luna<RenderPath_BindLua>::PropertyType properties[];

		RenderPath_BindLua() = default;
		RenderPath_BindLua(RenderPath* component) :component(component) {}
		RenderPath_BindLua(lua_State* L) {}

		virtual int GetLayerMask(lua_State* L);
		virtual int SetLayerMask(lua_State* L);

		static void Bind(lua_State* L);
	};
}
