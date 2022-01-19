#pragma once

#include "Vendors/lua/lua.hpp"
#include "vCommon.h"
#include "Core/Helpers/wiMath.h"
#include "Core/Helpers/wiUnorderedMap.h"
#include "Core/Helpers/wiVector.h"
#include "Core/Scripting/vLuaWrapper.h"
#include "Core/Scripting/vLuna.h"

#include <string>

typedef int(*lua_CFunction) (lua_State* L);
typedef struct lua_CInstance
{
    lua_State* instance = nullptr;
    int execStatus = 0;
} lua_CInstance;
typedef wi::unordered_map<lua_State*, lua_CInstance> lua_CInstancePool;

namespace wi::lua
{
	lua_State* GetInternalInstance();
	lua_CInstancePool GetInstancePool();

	void Initialize();

	//check if the last call succeeded
	bool Success(lua_State* L);
	//check if the last call failed
	bool Failed(lua_State* L);
	//get error message for the last call
	std::string GetErrorMsg(lua_State* L);
	//remove and get error message from stack
	std::string PopErrorMsg(lua_State* L);
	//post error to backlog and/or debug output
	void PostErrorMsg(lua_State* L);
	//run a script from file
	bool RunFile(lua_State* L, const std::string& filename);
	//run a script from param
	bool RunText(lua_State* L, const std::string& script);

	//send a signal to lua
	void Signal(const std::string& name);

	//kill every running background task (coroutine)
	void KillProcesses();
};