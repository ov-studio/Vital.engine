#pragma once
#include "Core/Scripting/wiLua.h"
#include "Core/Scripting/wiLuna.h"
#include "Core/Graphics/wiImage.h"

namespace wi::lua
{
	class ImageParams_BindLua
	{
	public:
		wi::image::Params params;

		static const char className[];
		static Luna<ImageParams_BindLua>::FunctionType methods[];
		static Luna<ImageParams_BindLua>::PropertyType properties[];

		ImageParams_BindLua(const wi::image::Params& params);
		ImageParams_BindLua(lua_State* L);

		int GetPos(lua_State* L);
		int GetSize(lua_State* L);
		int GetPivot(lua_State* L);
		int GetColor(lua_State* L);
		int GetOpacity(lua_State* L);
		int GetFade(lua_State* L);
		int GetRotation(lua_State* L);
		int GetTexOffset(lua_State* L);
		int GetTexOffset2(lua_State* L);
		int GetDrawRect(lua_State* L);
		int GetDrawRect2(lua_State* L);
		int IsDrawRectEnabled(lua_State* L);
		int IsDrawRect2Enabled(lua_State* L);
		int IsMirrorEnabled(lua_State* L);
		int IsBackgroundBlurEnabled(lua_State* L);
		int IsBackgroundEnabled(lua_State* L);

		int SetPos(lua_State* L);
		int SetSize(lua_State* L);
		int SetPivot(lua_State* L);
		int SetColor(lua_State* L);
		int SetOpacity(lua_State* L);
		int SetFade(lua_State* L);
		int SetStencil(lua_State* L);
		int SetStencilRefMode(lua_State* L);
		int SetBlendMode(lua_State* L);
		int SetQuality(lua_State* L);
		int SetSampleMode(lua_State* L);
		int SetRotation(lua_State* L);
		int SetTexOffset(lua_State* L);
		int SetTexOffset2(lua_State* L);
		int EnableDrawRect(lua_State* L);
		int EnableDrawRect2(lua_State* L);
		int DisableDrawRect(lua_State* L);
		int DisableDrawRect2(lua_State* L);
		int EnableMirror(lua_State* L);
		int DisableMirror(lua_State* L);
		int EnableBackgroundBlur(lua_State* L);
		int DisableBackgroundBlur(lua_State* L);
		int EnableBackground(lua_State* L);
		int DisableBackground(lua_State* L);

		static void Bind();
	};
}
