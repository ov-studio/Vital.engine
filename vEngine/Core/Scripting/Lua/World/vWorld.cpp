#include "Core/Scripting/Lua/Common/vGame.h"
#include "Core/Scripting/Lua/World/vWorld.h"

namespace wi::lua
{
    // Library Binder
    const char World::libraryName[] = "world";
    const luaL_Reg World::libraryFunctions[] = {
        { "clearScene", clearScene },
        { NULL, NULL }
    };

    // Instance Binder
    void World::Bind(lua_State* L)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            RegisterLibrary(L, World::libraryName, World::libraryFunctions, "vEngine");
        }
    }

    // Library Methods
    int clearScene(lua_State* L)
    {
        Scene_BindLua* scene = Luna<Scene_BindLua>::lightcheck(L, 1);
        bool clearAllScenes = wi::lua::SGetBool(L, 2) || false;
        if (clearAllScenes)
        {
            wi::renderer::ClearWorld(wi::scene::GetScene());
            wi::lua::SSetBool(L, true);
            return 1;
        }
        else if(scene)
        {
            wi::renderer::ClearWorld(*scene->scene);
            wi::lua::SSetBool(L, true);
            return 1;
        }
        wi::lua::SError(L, "Syntax: vEngine.world.ClearWorld(userdata scene, bool clearAll = false)");
        wi::lua::SSetBool(L, false);
        return 0;
    }
};
