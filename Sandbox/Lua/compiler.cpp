#include "../../vEngine/vEngine.h"

#include <iostream>
#include <filesystem>
#include <mutex>
#include <string>

std::mutex locker;
std::string modulePath = "Lua/";
static const wi::vector<std::string> SandboxModules = {
   "Client/init.lua"
};
wi::unordered_map<std::string, std::string> moduleResults;

int main()
{
	std::cout << "[Sandbox Compiler] Compiling Lua module" << std::endl;

	wi::jobsystem::Initialize();
	wi::jobsystem::context ctx;
	wi::helper::MakePathAbsolute(modulePath);
	wi::Timer timer;

	for (int i = 0; i < SandboxModules.size(); ++i)
    {
        wi::vector<uint8_t> fileData;
        if (wi::helper::FileRead(modulePath + SandboxModules[i], fileData))
		{
            std::string scriptData = std::string(fileData.begin(), fileData.end());
            wi::jobsystem::Execute(ctx, [=](wi::jobsystem::JobArgs args) {
				locker.lock();
				std::cout << "Script Compiled: " << SandboxModules[i] << std::endl;
				moduleResults[(SandboxModules[i])] = scriptData;
				locker.unlock();
			});
		}
    	else
		{
			locker.lock();
			std::cerr << "Script Compilation Failed: " << SandboxModules[i] << std::endl;
			locker.unlock();
			std::exit(1);
		}
    }
	wi::jobsystem::Wait(ctx);
	std::cout << "[Sandbox Compiler] Finished compiling Lua module in " << std::setprecision(4) << timer.elapsed_seconds() << " seconds" << std::endl;
	timer.record();

    std::string bundlerData;
    bundlerData += "namespace SandboxLua {\n";
	bundlerData += "wi::unordered_map<std::string, std::string> modules {\n";
	for (auto& x : moduleResults)
	{
		auto& name = x.first;
		auto& output = x.second;

		std::string name_repl = name;
		std::replace(name_repl.begin(), name_repl.end(), '/', '_');
		std::replace(name_repl.begin(), name_repl.end(), '.', '_');
		bundlerData += "const uint8_t " + name_repl + "[] = {";
		for (size_t i = 0; i < output.shadersize; ++i)
		{
			bundlerData += std::to_string((uint32_t)output.shaderdata[i]) + ",";
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

	return 0;
}
