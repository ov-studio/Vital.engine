#include "../../vEngine/vEngine.h"

#include <iostream>
#include <filesystem>
#include <mutex>
#include <string>

std::mutex locker;
static const wi::vector<std::string> SandboxModules = {
   "Client/init.lua"
};

int main()
{
	std::cout << "[Sandbox Compiler] Compiling Lua module" << std::endl;

	wi::jobsystem::Initialize();
	wi::jobsystem::context ctx;
	//std::string SHADERSOURCEPATH = "../../../" + wi::renderer::GetShaderSourcePath();
	//wi::helper::MakePathAbsolute(SHADERSOURCEPATH);
	wi::Timer timer;

	for (int i = 0; i < SandboxModules.size()); ++i)
    {
        std::cout<< "invoked..";
        std::cout<< SandboxModules[i];
    }

    /*
    		for (int i = 0; i < wiLua_Globals2.size(); i++)
		{
            wi::backlog::post("Lua/Globals/" + wiLua_Globals2[i]);
            RunFile("Lua/Globals/" + wiLua_Globals2[i]);
		}
    */

    /*
	for (auto& target : targets)
	{
		std::string SHADERPATH = SHADERSOURCEPATH + target.dir;
		wi::helper::DirectoryCreate(SHADERPATH);

			for (auto& shader : shaders[i])
			{
				wi::jobsystem::Execute(ctx, [=](wi::jobsystem::JobArgs args) {
					std::string shaderbinaryfilename = wi::helper::ReplaceExtension(SHADERPATH + shader, "cso");
					if (!rebuild && !wi::shadercompiler::IsShaderOutdated(shaderbinaryfilename))
					{
						return;
					}

					input.shadersourcefilename = SHADERSOURCEPATH + shader;
					input.include_directories.push_back(SHADERSOURCEPATH);

					auto it = minshadermodels.find(shader);
					if (it != minshadermodels.end())
					{
						// increase min shader model only for specific shaders
						input.minshadermodel = it->second;
					}
					if (input.minshadermodel > ShaderModel::SM_5_0 && target.format == ShaderFormat::HLSL5)
					{
						// if shader format cannot support shader model, then we cancel the task without returning error
						return;
					}

					wi::shadercompiler::CompilerOutput output;
					wi::shadercompiler::Compile(input, output);

					if (output.IsValid())
					{
						wi::shadercompiler::SaveShaderAndMetadata(shaderbinaryfilename, output);

						locker.lock();
						if (!output.error_message.empty())
						{
							std::cerr << output.error_message << std::endl;
						}
						std::cout << "Sandbox Compiled: " << shaderbinaryfilename << std::endl;
						if (shaderdump_enabled)
						{
							results[shaderbinaryfilename] = output;
						}
						locker.unlock();
					}
					else
					{
						locker.lock();
						std::cerr << "Sandbox Compilation Failed: " << shaderbinaryfilename << std::endl << output.error_message;
						locker.unlock();
						std::exit(1);
					}

					});
			}
		}
	}
    */
	wi::jobsystem::Wait(ctx);

	std::cout << "[Sandbox Compiler] Finished compiling Lua module in " << std::setprecision(4) << timer.elapsed_seconds() << " seconds" << std::endl;
	timer.record();
	/*
    std::string ss;
	ss += "namespace wiShaderDump {\n";
	for (auto& x : results)
	{
		auto& name = x.first;
		auto& output = x.second;

		std::string name_repl = name;
		std::replace(name_repl.begin(), name_repl.end(), '/', '_');
		std::replace(name_repl.begin(), name_repl.end(), '.', '_');
		ss += "const uint8_t " + name_repl + "[] = {";
		for (size_t i = 0; i < output.shadersize; ++i)
		{
			ss += std::to_string((uint32_t)output.shaderdata[i]) + ",";
		}
		ss += "};\n";
	}
	ss += "struct ShaderDumpEntry{const uint8_t* data; size_t size;};\n";
	ss += "const wi::unordered_map<std::string, ShaderDumpEntry> shaderdump = {\n";
	for (auto& x : results)
	{
		auto& name = x.first;
		auto& output = x.second;

		std::string name_repl = name;
		std::replace(name_repl.begin(), name_repl.end(), '/', '_');
		std::replace(name_repl.begin(), name_repl.end(), '.', '_');
		ss += "std::pair<std::string, ShaderDumpEntry>(\"" + name + "\", {" + name_repl + ",sizeof(" + name_repl + ")}),\n";
	}
	ss += "};\n"; // map end
	ss += "}\n"; // namespace end
	wi::helper::FileWrite("wiShaderDump.h", (uint8_t*)ss.c_str(), ss.length());
	std::cout << "[Sandbox Compiler] ShaderDump written to wiShaderDump.h in " << std::setprecision(4) << timer.elapsed_seconds() << " seconds" << std::endl;
    */

	return 0;
}
