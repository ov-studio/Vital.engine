#ifndef vEngine
    #define vEngine
    #include "vCommon.h"

    // Engine Interfaces:
    #include "Core/Interfaces/wiApplication.h"
    #include "Core/Interfaces/wiRenderPath.h"
    #include "Core/Interfaces/wiRenderPath2D.h"
    #include "Core/Interfaces/wiRenderPath3D.h"
    #include "Core/Interfaces/wiRenderPath3D_PathTracing.h"
    #include "Core/Interfaces/wiLoadingScreen.h"

    // Engine Essentials
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
    #include "Core/Graphics/wiTextureHelper.h"
    #include "Core/Helpers/wiRandom.h"
    #include "Core/Helpers/wiColor.h"
    #include "Core/Physics/wiPhysics.h"
    #include "Core/Graphics/wiEnums.h"
    #include "Core/Systems/wiInitializer.h"
    #include "Core/Browser/vBrowser.h"
    #include "Core/Scripting/Lua/vLuaBooter.h"
    #include "Core/Sandbox/vImporter.h"
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

    #pragma comment(lib,"vEngine_CEF.lib")
    #ifdef _WIN32
        #ifdef PLATFORM_UWP
            #pragma comment(lib,"vEngine_UWP.lib")
        #else
            #pragma comment(lib,"vEngine_Windows.lib")
        #endif
    #endif
#endif
