#pragma once
#include "Core/Scripting/vLuaBooter.h"
#include "Core/Graphics/API/wiGraphics.h"

namespace wi::lua
{
	class Texture
	{
        public:
            wi::graphics::Texture texture;
            static const char className[];
            static Luna<Texture>::FunctionType methods[];
            static Luna<Texture>::PropertyType properties[];
            Texture(lua_State* L) {};
            static void Bind(lua_State* L);
	};

}
