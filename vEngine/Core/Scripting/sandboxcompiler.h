#include "commonInclude.h"
#include "Core/Helpers/wiHelper.h"
#include "Core/Systems/wiJobSystem.h"
#include "Core/Helpers/wiVector.h"

#include <string>

struct moduleDef
{
	std::string moduleName;
	wi::vector<std::string> moduleScripts;
};

int compileSandboxModule(std::string moduleName, wi::vector<moduleDef> modules);