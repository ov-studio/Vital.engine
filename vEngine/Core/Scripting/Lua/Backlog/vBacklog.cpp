#include "Core/Scripting/Lua/Backlog/vBacklog.h"
#include "Core/Tools/wiBacklog.h"

#include <string>

namespace wi::lua
{
    // Library Binder
    const char Backlog::libraryName[] = "backlog";
    const luaL_Reg Backlog::libraryFunctions[] = {
        { "clear", clear },
        { "post", post },
        { "isActive", isActive },
        { "setLevel", setLevel },
        { NULL, NULL }
    };

    // Instance Binder
    void Backlog::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            RegisterLibrary(L, Backlog::libraryName, Backlog::libraryFunctions, "vEngine");
        }
    }

    // Library Methods
    int Backlog::clear(lua_State* L)
    {
        wi::backlog::clear();
        wi::lua::SSetBool(L, true);
        return 1;
    }
    int Backlog::post(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc < 2)
        {
            wi::lua::SError(L, "Syntax: vEngine.backlog.post(string message, int level)!");
            wi::lua::SSetBool(L, false);
            return 0;
        }
        wi::backlog::post(wi::lua::SGetString(L, 1), (wi::backlog::LogLevel)wi::lua::SGetInt(L, 2));
        wi::lua::SSetBool(L, true);
        return 1;
    }
    int Backlog::isActive(lua_State* L)
    {
        wi::lua::SSetBool(L, wi::backlog::isActive());
        return 1;
    }
    int Backlog::setLevel(lua_State* L)
    {
        int argc = wi::lua::SGetArgCount(L);
        if (argc <= 1)
        {
            wi::lua::SError(L, "Syntax: vEngine.backlog.setLevel(int level)");
            wi::lua::SSetBool(L, false);
            return 0;
        }
        wi::backlog::SetLogLevel((wi::backlog::LogLevel)wi::lua::SGetInt(L, 1));
        wi::lua::SSetBool(L, true);
        return 1;
    }
}