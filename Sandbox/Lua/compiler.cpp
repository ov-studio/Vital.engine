#include "../../vEngine/vEngine.h"

#include <iostream>
#include <filesystem>
#include <mutex>
#include <string>

std::mutex locker;
std::string modulePath = "Lua/";
struct moduleTypes
{
	std::string moduleName;
	wi::vector<std::string> moduleScripts;
};
wi::vector<moduleTypes> SandboxModule = {
    {
        "Shared",
        {
            "init.lua"
        }
    },
    {
        "Client",
        {}
    },
    {
        "Server",
        {}
    }
};

wi::unordered_map<std::string, std::string> moduleResults;

int main()
{
	std::cout << "[Sandbox Compiler] Compiling Lua module" << std::endl;

	wi::jobsystem::Initialize();
	wi::jobsystem::context ctx;
	wi::helper::MakePathAbsolute(modulePath);
	wi::Timer timer;

	for (int i = 0; i < SandboxModule.size(); ++i)
    {
        std::cout << SandboxModule[i].moduleName << std::endl;
		for (int j = 0; j < SandboxModule[i].moduleScripts.size(); ++j)
		{
            wi::vector<uint8_t> fileData;
            std::string scriptPath = SandboxModule[i].moduleScripts[j];
            if (wi::helper::FileRead(modulePath + scriptPath, fileData))
            {
                std::string scriptData = std::string(fileData.begin(), fileData.end());
                wi::jobsystem::Execute(ctx, [=](wi::jobsystem::JobArgs args) {
                    locker.lock();
                    std::cout << "Script Compiled: " << scriptPath << std::endl;
                    //moduleResults[(scriptPath)] = scriptData;
                    locker.unlock();
                });
            }
            else
            {
                locker.lock();
                std::cerr << "Script Compilation Failed: " << scriptPath << std::endl;
                locker.unlock();
                std::exit(1);
            }
		}
    }
	wi::jobsystem::Wait(ctx);
	std::cout << "[Sandbox Compiler] Finished compiling Lua module in " << std::setprecision(4) << timer.elapsed_seconds() << " seconds" << std::endl;
	timer.record();

    /*
    std::string bundlerData;
    bundlerData += "namespace SandboxLua {\n";
	bundlerData += "wi::unordered_map<std::string, std::string> modules {\n";

    bundlerData += "wi::unordered_map<std::string, std::string> " + "Client" + "[] = {}";
	for (auto& x : moduleResults)
	{
		auto& name = x.first;
		auto& output = x.second;

		std::string name_repl = name;
		bundlerData += x.second + ",";

		for (size_t i = 0; i < output.shadersize; ++i)
		{
			bundlerData += x.second + ",";
		}
		bundlerData += "};\n";
	}
	bundlerData += "struct ShaderDumpEntry{const uint8_t* data; size_t size;};\n";
	bundlerData += "const wi::unordered_map<std::string, ShaderDumpEntry> shaderdump = {\n";
	for (auto& x : moduleResults)
	{
		auto& name = x.first;
		auto& output = x.second;

		std::string name_repl = name;
		std::replace(name_repl.begin(), name_repl.end(), '/', '_');
		std::replace(name_repl.begin(), name_repl.end(), '.', '_');
		bundlerData += "std::pair<std::string, ShaderDumpEntry>(\"" + name + "\", {" + name_repl + ",sizeof(" + name_repl + ")}),\n";
	}
	bundlerData += "};\n"; // map end
	bundlerData += "}\n"; // namespace end
	wi::helper::FileWrite("wiSandboxLua.h", (uint8_t*)bundlerData.c_str(), bundlerData.length());
	std::cout << "[Sandbox Compiler] ScriptDump written to wiSandboxLua.h in " << std::setprecision(4) << timer.elapsed_seconds() << " seconds" << std::endl;
    */

	return 0;
}
