#include "../../vEngine.h"

#include <iostream>
#include <filesystem>
#include <mutex>
#include <string>

std::mutex locker;

using namespace wi::graphics;

wi::vector<std::string> shaders[static_cast<size_t>(ShaderStage::Count)];
wi::unordered_map<std::string, ShaderModel> minshadermodels;
struct Target
{
	ShaderFormat format;
	std::string dir;
};
wi::unordered_map<std::string, wi::shadercompiler::CompilerOutput> results;
wi::vector<Target> targets = {
    { ShaderFormat::HLSL6, "hlsl6/" },
	{ ShaderFormat::SPIRV, "spirv/" }
};

int main()
{
    std::cout << "[Sandbox Compiler] Compiling shaders" << std::endl;
	wi::jobsystem::Initialize();
	std::cout << std::endl;

	shaders[static_cast<size_t>(ShaderStage::CS)] = {
		"hairparticle_simulateCS.hlsl",
		"hairparticle_finishUpdateCS.hlsl",
		"emittedparticle_simulateCS.hlsl",
		"generateMIPChainCubeCS_float4.hlsl",
		"generateMIPChainCubeCS_unorm4.hlsl",
		"generateMIPChainCubeArrayCS_float4.hlsl",
		"generateMIPChainCubeArrayCS_unorm4.hlsl",
		"generateMIPChain3DCS_float4.hlsl",
		"generateMIPChain3DCS_unorm4.hlsl",
		"generateMIPChain2DCS_float4.hlsl",
		"generateMIPChain2DCS_unorm4.hlsl",
		"blur_gaussian_float4CS.hlsl",
		"bloomseparateCS.hlsl",
		"depthoffield_mainCS.hlsl",
		"depthoffield_neighborhoodMaxCOCCS.hlsl",
		"depthoffield_prepassCS.hlsl",
		"depthoffield_upsampleCS.hlsl",
		"depthoffield_tileMaxCOC_verticalCS.hlsl",
		"depthoffield_tileMaxCOC_horizontalCS.hlsl",
		"voxelRadianceSecondaryBounceCS.hlsl",
		"voxelSceneCopyClearCS.hlsl",
		"voxelClearOnlyNormalCS.hlsl",
		"upsample_bilateral_float1CS.hlsl",
		"upsample_bilateral_float4CS.hlsl",
		"upsample_bilateral_unorm1CS.hlsl",
		"upsample_bilateral_unorm4CS.hlsl",
		"temporalaaCS.hlsl",
		"tileFrustumsCS.hlsl",
		"tonemapCS.hlsl",
		"fsr_upscalingCS.hlsl",
		"fsr_sharpenCS.hlsl",
		"ssaoCS.hlsl",
		"rtreflectionCS.hlsl",
		"ssr_raytraceCS.hlsl",
		"ssr_resolveCS.hlsl",
		"ssr_temporalCS.hlsl",
		"ssr_medianCS.hlsl",
		"sharpenCS.hlsl",
		"skinningCS.hlsl",
		"resolveMSAADepthStencilCS.hlsl",
		"raytraceCS.hlsl",
		"raytraceCS_rtapi.hlsl",
		"paint_textureCS.hlsl",
		"oceanUpdateDisplacementMapCS.hlsl",
		"oceanUpdateGradientFoldingCS.hlsl",
		"oceanSimulatorCS.hlsl",
		"msao_interleaveCS.hlsl",
		"msao_preparedepthbuffers1CS.hlsl",
		"msao_preparedepthbuffers2CS.hlsl",
		"msao_blurupsampleCS.hlsl",
		"msao_blurupsampleCS_blendout.hlsl",
		"msao_blurupsampleCS_premin.hlsl",
		"msao_blurupsampleCS_premin_blendout.hlsl",
		"msaoCS.hlsl",
		"motionblur_neighborhoodMaxVelocityCS.hlsl",
		"motionblur_tileMaxVelocity_horizontalCS.hlsl",
		"motionblur_tileMaxVelocity_verticalCS.hlsl",
		"luminancePass2CS.hlsl",
		"motionblur_kickjobsCS.hlsl",
		"motionblurCS.hlsl",
		"motionblurCS_cheap.hlsl",
		"motionblurCS_earlyexit.hlsl",
		"luminancePass1CS.hlsl",
		"lightShaftsCS.hlsl",
		"lightCullingCS_ADVANCED_DEBUG.hlsl",
		"lightCullingCS_DEBUG.hlsl",
		"lightCullingCS.hlsl",
		"lightCullingCS_ADVANCED.hlsl",
		"hbaoCS.hlsl",
		"gpusortlib_sortInnerCS.hlsl",
		"gpusortlib_sortStepCS.hlsl",
		"gpusortlib_kickoffSortCS.hlsl",
		"gpusortlib_sortCS.hlsl",
		"fxaaCS.hlsl",
		"filterEnvMapCS.hlsl",
		"fft_512x512_c2c_CS.hlsl",
		"fft_512x512_c2c_v2_CS.hlsl",
		"emittedparticle_sphpartitionCS.hlsl",
		"emittedparticle_sphpartitionoffsetsCS.hlsl",
		"emittedparticle_sphpartitionoffsetsresetCS.hlsl",
		"emittedparticle_simulateCS_SORTING.hlsl",
		"emittedparticle_simulateCS_SORTING_DEPTHCOLLISIONS.hlsl",
		"emittedparticle_sphdensityCS.hlsl",
		"emittedparticle_sphforceCS.hlsl",
		"emittedparticle_kickoffUpdateCS.hlsl",
		"emittedparticle_simulateCS_DEPTHCOLLISIONS.hlsl",
		"emittedparticle_emitCS.hlsl",
		"emittedparticle_emitCS_FROMMESH.hlsl",
		"emittedparticle_emitCS_volume.hlsl",
		"emittedparticle_finishUpdateCS.hlsl",
		"downsample4xCS.hlsl",
		"depthoffield_prepassCS_earlyexit.hlsl",
		"depthoffield_mainCS_cheap.hlsl",
		"depthoffield_mainCS_earlyexit.hlsl",
		"depthoffield_postfilterCS.hlsl",
		"depthoffield_kickjobsCS.hlsl",
		"copytexture2D_float4_borderexpandCS.hlsl",
		"copytexture2D_unorm4_borderexpandCS.hlsl",
		"copytexture2D_unorm4CS.hlsl",
		"copytexture2D_float4CS.hlsl",
		"chromatic_aberrationCS.hlsl",
		"bvh_hierarchyCS.hlsl",
		"bvh_primitivesCS.hlsl",
		"bvh_propagateaabbCS.hlsl",
		"blur_gaussian_wide_unorm1CS.hlsl",
		"blur_gaussian_wide_unorm4CS.hlsl",
		"blur_gaussian_unorm1CS.hlsl",
		"blur_gaussian_unorm4CS.hlsl",
		"blur_gaussian_wide_float1CS.hlsl",
		"blur_gaussian_wide_float3CS.hlsl",
		"blur_gaussian_wide_float4CS.hlsl",
		"blur_bilateral_wide_unorm4CS.hlsl",
		"blur_gaussian_float1CS.hlsl",
		"blur_gaussian_float3CS.hlsl",
		"blur_bilateral_unorm4CS.hlsl",
		"blur_bilateral_wide_float1CS.hlsl",
		"blur_bilateral_wide_float3CS.hlsl",
		"blur_bilateral_wide_float4CS.hlsl",
		"blur_bilateral_wide_unorm1CS.hlsl",
		"blur_bilateral_float1CS.hlsl",
		"blur_bilateral_float3CS.hlsl",
		"blur_bilateral_float4CS.hlsl",
		"blur_bilateral_unorm1CS.hlsl",
		"voxelSceneCopyClearCS_TemporalSmoothing.hlsl",
		"normalsfromdepthCS.hlsl",
		"volumetricCloud_shapenoiseCS.hlsl",
		"volumetricCloud_detailnoiseCS.hlsl",
		"volumetricCloud_curlnoiseCS.hlsl",
		"volumetricCloud_weathermapCS.hlsl",
		"volumetricCloud_renderCS.hlsl",
		"volumetricCloud_reprojectCS.hlsl",
		"volumetricCloud_temporalCS.hlsl",
		"shadingRateClassificationCS.hlsl",
		"shadingRateClassificationCS_DEBUG.hlsl",
		"skyAtmosphere_transmittanceLutCS.hlsl",
		"skyAtmosphere_skyViewLutCS.hlsl",
		"skyAtmosphere_multiScatteredLuminanceLutCS.hlsl",
		"skyAtmosphere_skyLuminanceLutCS.hlsl",
		"upsample_bilateral_uint4CS.hlsl",
		"screenspaceshadowCS.hlsl",
		"rtshadowCS.hlsl",
		"rtshadow_denoise_tileclassificationCS.hlsl",
		"rtshadow_denoise_filterCS.hlsl",
		"rtshadow_denoise_temporalCS.hlsl",
		"rtaoCS.hlsl",
		"rtao_denoise_tileclassificationCS.hlsl",
		"rtao_denoise_filterCS.hlsl",
		"visibility_resolveCS.hlsl",
		"visibility_resolveCS_MSAA.hlsl",
		"surfel_coverageCS.hlsl",
		"surfel_indirectprepareCS.hlsl",
		"surfel_updateCS.hlsl",
		"surfel_gridresetCS.hlsl",
		"surfel_gridoffsetsCS.hlsl",
		"surfel_binningCS.hlsl",
		"surfel_raytraceCS_rtapi.hlsl",
		"surfel_raytraceCS.hlsl"
	};
	shaders[static_cast<size_t>(ShaderStage::PS)] = {
		"emittedparticlePS_soft.hlsl",
		"imagePS.hlsl",
		"emittedparticlePS_soft_lighting.hlsl",
		"oceanSurfacePS.hlsl",
		"hairparticlePS.hlsl",
		"impostorPS.hlsl",
		"volumetricLight_SpotPS.hlsl",
		"volumetricLight_PointPS.hlsl",
		"volumetricLight_DirectionalPS.hlsl",
		"voxelPS.hlsl",
		"vertexcolorPS.hlsl",
		"upsample_bilateralPS.hlsl",
		"sunPS.hlsl",
		"skyPS_dynamic.hlsl",
		"skyPS_static.hlsl",
		"shadowPS_transparent.hlsl",
		"shadowPS_water.hlsl",
		"shadowPS_alphatest.hlsl",
		"renderlightmapPS.hlsl",
		"renderlightmapPS_rtapi.hlsl",
		"raytrace_debugbvhPS.hlsl",
		"outlinePS.hlsl",
		"oceanSurfaceSimplePS.hlsl",
		"objectPS_transparent_pom.hlsl",
		"objectPS_water.hlsl",
		"objectPS_voxelizer.hlsl",
		"objectPS_voxelizer_terrain.hlsl",
		"objectPS_transparent.hlsl",
		"objectPS_transparent_planarreflection.hlsl",
		"objectPS_planarreflection.hlsl",
		"objectPS_pom.hlsl",
		"objectPS_terrain.hlsl",
		"objectPS.hlsl",
		"objectPS_hologram.hlsl",
		"objectPS_paintradius.hlsl",
		"objectPS_simple.hlsl",
		"objectPS_debug.hlsl",
		"objectPS_prepass.hlsl",
		"objectPS_prepass_alphatest.hlsl",
		"objectPS_anisotropic.hlsl",
		"objectPS_transparent_anisotropic.hlsl",
		"objectPS_cloth.hlsl",
		"objectPS_transparent_cloth.hlsl",
		"objectPS_clearcoat.hlsl",
		"objectPS_transparent_clearcoat.hlsl",
		"objectPS_cloth_clearcoat.hlsl",
		"objectPS_transparent_cloth_clearcoat.hlsl",
		"objectPS_cartoon.hlsl",
		"objectPS_transparent_cartoon.hlsl",
		"objectPS_unlit.hlsl",
		"objectPS_transparent_unlit.hlsl",
		"lightVisualizerPS.hlsl",
		"lensFlarePS.hlsl",
		"impostorPS_wire.hlsl",
		"impostorPS_simple.hlsl",
		"impostorPS_prepass.hlsl",
		"hairparticlePS_simple.hlsl",
		"hairparticlePS_prepass.hlsl",
		"forceFieldVisualizerPS.hlsl",
		"fontPS.hlsl",
		"envMap_skyPS_static.hlsl",
		"envMap_skyPS_dynamic.hlsl",
		"envMapPS.hlsl",
		"envMapPS_terrain.hlsl",
		"emittedparticlePS_soft_distortion.hlsl",
		"downsampleDepthBuffer4xPS.hlsl",
		"emittedparticlePS_simple.hlsl",
		"cubeMapPS.hlsl",
		"circlePS.hlsl",
		"captureImpostorPS_normal.hlsl",
		"captureImpostorPS_surface.hlsl",
		"captureImpostorPS_albedo.hlsl"
	};
	shaders[static_cast<size_t>(ShaderStage::VS)] = {
		"hairparticleVS.hlsl",
		"emittedparticleVS.hlsl",
		"imageVS.hlsl",
		"fontVS.hlsl",
		"voxelVS.hlsl",
		"vertexcolorVS.hlsl",
		"volumetriclight_directionalVS.hlsl",
		"volumetriclight_pointVS.hlsl",
		"volumetriclight_spotVS.hlsl",
		"vSpotLightVS.hlsl",
		"vPointLightVS.hlsl",
		"sphereVS.hlsl",
		"skyVS.hlsl",
		"shadowVS_transparent.hlsl",
		"shadowVS.hlsl",
		"shadowVS_alphatest.hlsl",
		"postprocessVS.hlsl",
		"renderlightmapVS.hlsl",
		"raytrace_screenVS.hlsl",
		"oceanSurfaceVS.hlsl",
		"objectVS_simple.hlsl",
		"objectVS_voxelizer.hlsl",
		"objectVS_common.hlsl",
		"objectVS_common_tessellation.hlsl",
		"objectVS_prepass.hlsl",
		"objectVS_prepass_alphatest.hlsl",
		"objectVS_prepass_tessellation.hlsl",
		"objectVS_prepass_alphatest_tessellation.hlsl",
		"objectVS_simple_tessellation.hlsl",
		"objectVS_debug.hlsl",
		"lensFlareVS.hlsl",
		"impostorVS.hlsl",
		"forceFieldPointVisualizerVS.hlsl",
		"forceFieldPlaneVisualizerVS.hlsl",
		"envMap_skyVS.hlsl",
		"envMapVS.hlsl",
		"envMap_skyVS_emulation.hlsl",
		"envMapVS_emulation.hlsl",
		"cubeShadowVS.hlsl",
		"cubeShadowVS_alphatest.hlsl",
		"cubeShadowVS_emulation.hlsl",
		"cubeShadowVS_alphatest_emulation.hlsl",
		"cubeShadowVS_transparent.hlsl",
		"cubeShadowVS_transparent_emulation.hlsl",
		"occludeeVS.hlsl"
	};
	shaders[static_cast<size_t>(ShaderStage::GS)] = {
		"envMap_skyGS_emulation.hlsl",
		"envMapGS_emulation.hlsl",
		"cubeShadowGS_emulation.hlsl",
		"cubeShadowGS_alphatest_emulation.hlsl",
		"cubeShadowGS_transparent_emulation.hlsl",
		"voxelGS.hlsl",
		"objectGS_voxelizer.hlsl"
	};
	shaders[static_cast<size_t>(ShaderStage::DS)] = {
		"objectDS.hlsl",
		"objectDS_prepass.hlsl",
		"objectDS_prepass_alphatest.hlsl",
		"objectDS_simple.hlsl"
	};
	shaders[static_cast<size_t>(ShaderStage::HS)] = {
		"objectHS.hlsl",
		"objectHS_prepass.hlsl",
		"objectHS_prepass_alphatest.hlsl",
		"objectHS_simple.hlsl",
	};
	shaders[static_cast<size_t>(ShaderStage::AS)] = {

	};
	shaders[static_cast<size_t>(ShaderStage::MS)] = {
		"emittedparticleMS.hlsl",
	};
	shaders[static_cast<size_t>(ShaderStage::LIB)] = {
		"rtreflectionLIB.hlsl",
	};

	minshadermodels["renderlightmapPS_rtapi.hlsl"] = ShaderModel::SM_6_5;
	minshadermodels["raytraceCS_rtapi.hlsl"] = ShaderModel::SM_6_5;
	minshadermodels["rtshadowCS.hlsl"] = ShaderModel::SM_6_5;
	minshadermodels["rtaoCS.hlsl"] = ShaderModel::SM_6_5;
	minshadermodels["surfel_raytraceCS_rtapi.hlsl"] = ShaderModel::SM_6_5;
	minshadermodels["rtreflectionCS.hlsl"] = ShaderModel::SM_6_5;

	wi::jobsystem::context ctx;
	std::string sourcePath = "../" + wi::renderer::GetShaderSourcePath();
	wi::helper::MakePathAbsolute(sourcePath);
	wi::Timer timer;

    std::string bundlerData = "namespace viShaderDump {\n";
	for (auto& target : targets)
	{
		std::string shaderDirectory = sourcePath + target.dir;
		wi::helper::DirectoryCreate(shaderDirectory);
		for (int i = 0; i < static_cast<int>(ShaderStage::Count); ++i)
		{
			for (auto& shader : shaders[i])
			{
				wi::jobsystem::Execute(ctx, [=](wi::jobsystem::JobArgs args) {
					std::string shaderbinaryfilename = wi::helper::ReplaceExtension(shaderDirectory + shader, "cso");
					wi::shadercompiler::CompilerInput input;
					input.format = target.format;
					input.stage = (ShaderStage)i;
					input.shadersourcefilename = sourcePath + shader;
					input.include_directories.push_back(sourcePath);
					auto it = minshadermodels.find(shader);
					if (it != minshadermodels.end())
						input.minshadermodel = it->second;
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
						std::cout << "Shader Compiled: " << shaderbinaryfilename << std::endl;
						results[shaderbinaryfilename] = output;
						locker.unlock();
					}
					else
					{
						locker.lock();
						std::cerr << "Shader Compilation Failed: " << shaderbinaryfilename << std::endl << output.error_message;
						locker.unlock();
						std::exit(1);
					}
				});
			}
		}
	}

	wi::jobsystem::Wait(ctx);
	for (auto& x : results)
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
	for (auto& x : results)
	{
		auto& name = x.first;
		auto& output = x.second;
		std::string name_repl = name;
		std::replace(name_repl.begin(), name_repl.end(), '/', '_');
		std::replace(name_repl.begin(), name_repl.end(), '.', '_');
		bundlerData += "std::pair<std::string, ShaderDumpEntry>(\"" + name + "\", {" + name_repl + ",sizeof(" + name_repl + ")}),\n";
	}
	bundlerData += "};\n}\n";

    timer.record();
	//wi::helper::FileWrite("../viShaderDump.h", (uint8_t*)bundlerData .c_str(), bundlerData .length());
    //std::cout << "[Shader Compiler] Finished compiling shaders in " << std::setprecision(4) << timer.elapsed_seconds() << " seconds" << std::endl;
	return 0;
}