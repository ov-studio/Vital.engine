#include "Core/Scripting/Lua/Backlog/vBacklog.h"
#include "Core/Tools/wiBacklog.h"

#include <string>

namespace wi::lua
{
    // Class Binder
    const char Backlog::className[] = "backlog";
    Luna<Backlog>::FunctionType Backlog::methods[] = {
		lunamethod(Backlog, clear),
        lunamethod(Backlog, post),
        lunamethod(Backlog, isActive),
        lunamethod(Backlog, setLevel),
	    { NULL, NULL }
    };
    Luna<Backlog>::PropertyType Backlog::properties[] = {
	    { NULL, NULL }
    };
    void Backlog::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            Luna<Backlog>::Register(L, "vEngine");
            wi::lua::RunText(L, "vEngine.backlog = backlog()");
        }
    };

    // Class Methods
	int Backlog::clear(lua_State* L)
	{
		wi::backlog::clear();
        return 1;
	};

	int Backlog::post(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		std::string inputString;
		for (int i = 1; i <= argc; i++)
		{
			inputString += wi::lua::SGetString(L, i);
		}
		if (!inputString.empty())
		    wi::backlog::post(inputString);
        return 1;
	};

	int Backlog::isActive(lua_State* L)
	{
		wi::lua::SSetBool(L, wi::backlog::isActive());
        return 1;
	};

	int Backlog::setLevel(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
			wi::backlog::SetLogLevel((wi::backlog::LogLevel)wi::lua::SGetInt(L, 1));
		else
			wi::lua::SError(L, "setLevel(int val) not enough arguments!");
        return 1;
	};
}