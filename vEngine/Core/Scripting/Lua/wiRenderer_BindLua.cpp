#include "Core/Scripting/Lua/wiRenderer_BindLua.h"
#include "Core/Graphics/wiRenderer.h"
#include "Core/Helpers/wiHelper.h"
#include "Core/Systems/wiScene.h"
#include "Core/Scripting/Lua/wiScene_BindLua.h"
#include "Core/Scripting/Lua/Math/vMath.h"
#include "Core/Scripting/Lua/Texture/vTexture.h"
#include "Core/Graphics/wiEmittedParticle.h"
#include "Core/Graphics/wiHairParticle.h"
#include "Core/Scripting/Lua/wiPrimitive_BindLua.h"
#include "Core/Systems/wiEventHandler.h"

using namespace wi::ecs;
using namespace wi::graphics;
using namespace wi::scene;
using namespace wi::lua::scene;
using namespace wi::lua::primitive;

namespace wi::lua::renderer
{
	int SetGameSpeed(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::renderer::SetGameSpeed(wi::lua::SGetFloat(L, 1));
		}
		else
		{
			wi::lua::SError(L,"SetGameSpeed(float) not enough arguments!");
		}
		return 0;
	}
	int GetGameSpeed(lua_State* L)
	{
		wi::lua::SSetFloat(L, wi::renderer::GetGameSpeed());
		return 1;
	}

	int SetShadowProps2D(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 1)
		{
			wi::renderer::SetShadowProps2D(wi::lua::SGetInt(L, 1), wi::lua::SGetInt(L, 2));
		}
		else
			wi::lua::SError(L, "SetShadowProps2D(int resolution, int count) not enough arguments!");
		return 0;
	}
	int SetShadowPropsCube(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 1)
		{
			wi::renderer::SetShadowPropsCube(wi::lua::SGetInt(L, 1), wi::lua::SGetInt(L, 2));
		}
		else
			wi::lua::SError(L, "SetShadowPropsCube(int resolution, int count) not enough arguments!");
		return 0;
	}
	int SetDebugPartitionTreeEnabled(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::renderer::SetToDrawDebugPartitionTree(wi::lua::SGetBool(L, 1));
		}
		return 0;
	}
	int SetDebugBonesEnabled(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::renderer::SetToDrawDebugBoneLines(wi::lua::SGetBool(L, 1));
		}
		return 0;
	}
	int SetDebugEmittersEnabled(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::renderer::SetToDrawDebugEmitters(wi::lua::SGetBool(L, 1));
		}
		return 0;
	}
	int SetDebugForceFieldsEnabled(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::renderer::SetToDrawDebugForceFields(wi::lua::SGetBool(L, 1));
		}
		return 0;
	}
	int SetVSyncEnabled(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::eventhandler::SetVSync(wi::lua::SGetBool(L, 1));
		}
		return 0;
	}
	int SetDebugLightCulling(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::renderer::SetDebugLightCulling(wi::lua::SGetBool(L, 1));
		}
		else
		{
			wi::lua::SError(L, "SetDebugLightCulling(bool enabled) not enough arguments!");
		}
		return 0;
	}
	int SetOcclusionCullingEnabled(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::renderer::SetOcclusionCullingEnabled(wi::lua::SGetBool(L, 1));
		}
		else
		{
			wi::lua::SError(L, "SetOcclusionCullingEnabled(bool enabled) not enough arguments!");
		}
		return 0;
	}

	int DrawLine(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 1)
		{
			Vector* a = Luna<Vector>::lightcheck(L, 1);
			Vector* b = Luna<Vector>::lightcheck(L, 2);
			if (a && b)
			{
				wi::renderer::RenderableLine line;
				XMStoreFloat3(&line.start, XMLoadFloat4(a));
				XMStoreFloat3(&line.end, XMLoadFloat4(b));
				if (argc > 2)
				{
					Vector* c = Luna<Vector>::lightcheck(L, 3);
					if (c)
					{
						XMStoreFloat4(&line.color_start, XMLoadFloat4(c));
						XMStoreFloat4(&line.color_end, XMLoadFloat4(c));
					}
					else
						wi::lua::SError(L, "DrawLine(Vector origin,end, opt Vector color) one or more arguments are not vectors!");
				}
				wi::renderer::DrawLine(line);
			}
			else
				wi::lua::SError(L, "DrawLine(Vector origin,end, opt Vector color) one or more arguments are not vectors!");
		}
		else
			wi::lua::SError(L, "DrawLine(Vector origin,end, opt Vector color) not enough arguments!");

		return 0;
	}
	int DrawPoint(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			Vector* a = Luna<Vector>::lightcheck(L, 1);
			if (a)
			{
				wi::renderer::RenderablePoint point;
				XMStoreFloat3(&point.position, XMLoadFloat4(a));
				if (argc > 1)
				{
					point.size = wi::lua::SGetFloat(L, 2);

					if (argc > 2)
					{
						Vector* color = Luna<Vector>::lightcheck(L, 3);
						point.color = *color;
					}
				}
				wi::renderer::DrawPoint(point);
			}
			else
				wi::lua::SError(L, "DrawPoint(Vector origin, opt float size, opt Vector color) first argument must be a Vector type!");
		}
		else
			wi::lua::SError(L, "DrawPoint(Vector origin, opt float size, opt Vector color) not enough arguments!");

		return 0;
	}
	int DrawBox(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			Matrix* m = Luna<Matrix>::lightcheck(L, 1);
			if (m)
			{
				if (argc > 1)
				{
					Vector* color = Luna<Vector>::lightcheck(L, 2);
					if (color)
					{
						wi::renderer::DrawBox(*m, *color);
						return 0;
					}
				}

				wi::renderer::DrawBox(*m);
			}
			else
				wi::lua::SError(L, "DrawBox(Matrix boxMatrix, opt Vector color) first argument must be a Matrix type!");
		}
		else
			wi::lua::SError(L, "DrawBox(Matrix boxMatrix, opt Vector color) not enough arguments!");

		return 0;
	}
	int DrawSphere(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			Sphere_BindLua* sphere = Luna<Sphere_BindLua>::lightcheck(L, 1);
			if (sphere)
			{
				if (argc > 1)
				{
					Vector* color = Luna<Vector>::lightcheck(L, 2);
					if (color)
					{
						wi::renderer::DrawSphere(sphere->sphere, *color);
						return 0;
					}
				}

				wi::renderer::DrawSphere(sphere->sphere);
			}
			else
				wi::lua::SError(L, "DrawSphere(Sphere sphere, opt Vector color) first argument must be a Matrix type!");
		}
		else
			wi::lua::SError(L, "DrawSphere(Sphere sphere, opt Vector color) not enough arguments!");

		return 0;
	}
	int DrawCapsule(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			Capsule_BindLua* capsule = Luna<Capsule_BindLua>::lightcheck(L, 1);
			if (capsule)
			{
				if (argc > 1)
				{
					Vector* color = Luna<Vector>::lightcheck(L, 2);
					if (color)
					{
						wi::renderer::DrawCapsule(capsule->capsule, *color);
						return 0;
					}
				}

				wi::renderer::DrawCapsule(capsule->capsule);
			}
			else
				wi::lua::SError(L, "DrawCapsule(Capsule capsule, opt Vector color) first argument must be a Matrix type!");
		}
		else
			wi::lua::SError(L, "DrawCapsule(Capsule capsule, opt Vector color) not enough arguments!");

		return 0;
	}
	int PutWaterRipple(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 1)
		{
			std::string name = wi::lua::SGetString(L, 1);
			Vector* v = Luna<Vector>::lightcheck(L, 2);
			if (v)
			{
                // TODO: GetScriptPath is removed, requires new method
				//XMFLOAT3 pos;
				//XMStoreFloat3(&pos, XMLoadFloat4(v));
				//wi::scene::GetScene().PutWaterRipple(wi::lua::GetScriptPath() + name, pos);
			}
			else
				wi::lua::SError(L, "PutWaterRipple(String imagename, Vector position) argument is not a Vector!");
		}
		else
			wi::lua::SError(L, "PutWaterRipple(String imagename, Vector position) not enough arguments!");
		return 0;
	}

	int ClearWorld(lua_State* L)
	{
		Scene_BindLua* scene = Luna<Scene_BindLua>::lightcheck(L, 1);
		if (scene == nullptr)
		{
			wi::renderer::ClearWorld(wi::scene::GetScene());
		}
		else
		{
			wi::renderer::ClearWorld(*scene->scene);
		}
		return 0;
	}
	int ReloadShaders(lua_State* L)
	{
		wi::renderer::ReloadShaders();
		return 0;
	}

	void Bind(lua_State* L)
	{
		static bool initialized = false;
		if (!initialized)
		{
			initialized = true;
			wi::lua::RegisterFunc(L, "SetGameSpeed", SetGameSpeed);
			wi::lua::RegisterFunc(L, "GetGameSpeed", GetGameSpeed);

			wi::lua::RunText(L, "GetScreenWidth = function() return main.GetCanvas().GetLogicalWidth() end");
			wi::lua::RunText(L, "GetScreenHeight = function() return main.GetCanvas().GetLogicalHeight() end");

			wi::lua::RegisterFunc(L, "SetShadowProps2D", SetShadowProps2D);
			wi::lua::RegisterFunc(L, "SetShadowPropsCube", SetShadowPropsCube);
			wi::lua::RegisterFunc(L, "SetDebugPartitionTreeEnabled", SetDebugPartitionTreeEnabled);
			wi::lua::RegisterFunc(L, "SetDebugBonesEnabled", SetDebugBonesEnabled);
			wi::lua::RegisterFunc(L, "SetDebugEmittersEnabled", SetDebugEmittersEnabled);
			wi::lua::RegisterFunc(L, "SetDebugForceFieldsEnabled", SetDebugForceFieldsEnabled);
			wi::lua::RegisterFunc(L, "SetVSyncEnabled", SetVSyncEnabled);
			wi::lua::RegisterFunc(L, "SetDebugLightCulling", SetDebugLightCulling);
			wi::lua::RegisterFunc(L, "SetOcclusionCullingEnabled", SetOcclusionCullingEnabled);

			wi::lua::RegisterFunc(L, "DrawLine", DrawLine);
			wi::lua::RegisterFunc(L, "DrawPoint", DrawPoint);
			wi::lua::RegisterFunc(L, "DrawBox", DrawBox);
			wi::lua::RegisterFunc(L, "DrawSphere", DrawSphere);
			wi::lua::RegisterFunc(L, "DrawCapsule", DrawCapsule);
			wi::lua::RegisterFunc(L, "PutWaterRipple", PutWaterRipple);


			wi::lua::RunText(L, "PICK_VOID = 0");
			wi::lua::RunText(L, "PICK_OPAQUE = 1");
			wi::lua::RunText(L, "PICK_TRANSPARENT = 2");
			wi::lua::RunText(L, "PICK_WATER = 4");


			wi::lua::RegisterFunc(L, "ClearWorld", ClearWorld);
			wi::lua::RegisterFunc(L, "ReloadShaders", ReloadShaders);
		}
	}
};
