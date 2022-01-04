#pragma once

#include "../vEngine/vEngine.h"

#include <string>

struct moduleDef
{
	std::string moduleName;
	wi::vector<std::string> moduleScripts;
};

int compileSandboxModule(std::string moduleName, wi::vector<moduleDef> modules);