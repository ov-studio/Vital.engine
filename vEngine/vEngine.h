#ifndef vEngine
#define vEngine

// NOTE:
// The purpose of this file is to expose all engine features.
// It should be included in the engine's implementing application not the engine itself!
// It should be included in the precompiled header if available.

#include "vCommon.h"

// High-level interface:
#include "Core/Interfaces/wiApplication.h"
#include "Core/Interfaces/wiRenderPath.h"
#include "Core/Interfaces/wiRenderPath2D.h"
#include "Core/Interfaces/wiRenderPath3D.h"
#include "Core/Interfaces/wiRenderPath3D_PathTracing.h"
#include "Core/Interfaces/wiLoadingScreen.h"

// Engine-level systems
#include "vVersion.h"
#include "Core/Systems/wiPlatform.h"
#include "Core/Tools/wiBacklog.h"
#include "Core/Helpers/wiPrimitive.h"
#include "Core/Graphics/wiImage.h"
#include "Core/Graphics/wiFont.h"
#include "Core/Graphics/wiSprite.h"
#include "Core/Graphics/wiSpriteFont.h"
#include "Core/Systems/wiScene.h"
#include "Core/Systems/wiECS.h"
#include "Core/Graphics/wiEmittedParticle.h"
#include "Core/Graphics/wiHairParticle.h"
#include "Core/Graphics/wiRenderer.h"
#include "Core/Helpers/wiMath.h"
#include "Core/Audio/wiAudio.h"
#include "Core/Helpers/wiResourceManager.h"
#include "Core/Helpers/wiTimer.h"
#include "Core/Helpers/wiHelper.h"
#include "Core/Input/wiInput.h"
#include "Core/Input/wiRawInput.h"
#include "Core/Input/wiXInput.h"
#include "Core/Input/wiSDLInput.h"
#include "Core/Graphics/wiTextureHelper.h"
#include "Core/Helpers/wiRandom.h"
#include "Core/Helpers/wiColor.h"
#include "Core/Physics/wiPhysics.h"
#include "Core/Graphics/wiEnums.h"
#include "Core/Systems/wiInitializer.h"
#include "Core/Scripting/wiLua.h"
#include "Core/Scripting/wiLuna.h"
#include "Core/Graphics/API/wiGraphics.h"
#include "Core/Graphics/API/wiGraphicsDevice.h"
#include "Core/Systems/wiGUI.h"
#include "Core/Helpers/wiArchive.h"
#include "Core/Helpers/wiSpinLock.h"
#include "Core/Helpers/wiRectPacker.h"
#include "Core/Tools/wiProfiler.h"
#include "Core/Graphics/wiOcean.h"
#include "Core/Graphics/wiFFTGenerator.h"
#include "Core/Helpers/wiArguments.h"
#include "Core/Graphics/wiGPUBVH.h"
#include "Core/Graphics/wiGPUSortLib.h"
#include "Core/Systems/wiJobSystem.h"
#include "Core/Network/wiNetwork.h"
#include "Core/Systems/wiEventHandler.h"
#include "Core/Graphics/API/wiShaderCompiler.h"
#include "Core/Systems/wiCanvas.h"
#include "Core/Helpers/wiUnorderedMap.h"
#include "Core/Helpers/wiUnorderedSet.h"
#include "Core/Helpers/wiVector.h"

#ifdef _WIN32
#ifdef PLATFORM_UWP
#pragma comment(lib,"vEngine_UWP.lib")
#else
#pragma comment(lib,"vEngine_Windows.lib")
#endif // PLATFORM_UWP
#endif // _WIN32

#endif // vEngine
