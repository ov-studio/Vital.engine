## ━ Pipelines:
  * DirectX 12
  * Vulkan

## ━ Renderers (Multi Threaded):
  * Images
  * Fonts (True Type)
  * 3D mesh
  * Sprites

## ━ Shader Maps:
  * Normal mapping
  * Displacement mapping
  * Parallax occlusion mapping
  * Dynamic environment mapping

## ━ Anti Aliasings:
  * FXAA
  * TAA (Temporal Anti-aliasing)
  * MSAA (Forward rendering only)

## ━ Filters:
  * Supersampling
  * Bloom
  * Edge outline
  * Motion Blur
  * Lens Flare
  * Light shafts
  * Bokeh Depth of Field
  * Chromatic aberration
  * Tessellation (silhouette smoothing, displacement mapping)
  * Cube map reflections (static and real time)
  * Real time planar reflections
  * Color Grading
  * Sharpen filter
  * Eye adaption
  * Refractions

## ━ AOs:
  * SSAO
  * HBAO
  * MSAO

## ━ Environments:
  * Skybox
  * Waterbox (FFT Simulation)
  * Soft particles
  * GPU-based particles (emit from point, mesh, animated mesh)
  * Hair particle systems (Grass/Vegetation)
  * Terrain Rendering (material blending)
  * Variable Rate Shading
  * Real time ray tracing: ambient occlusion, shadows, reflections (DXR and Vulkan raytracing)
  * Screen Space Contact Shadows
  * Stochastic alphatest transparency
  * Surfel GI
  * Soft shadows (PCF)

## ━ Models:
  * GLTF
  * Skeletal animation
  * Morph target animation

* Networking (UDP)
* Instanced rendering
* Directional lights + cascaded shadow maps
* Spotlights + shadow maps
* Point lights + shadow cubemaps
* BULLET Physics: rigid body, soft body

3D Audio (Xaudio2)
Input: keyboard, mouse, controller (rawinput, xinput), touch
Controller feedback (vibration, LED)
Backlog: log,input,scripting
Gamma correct, HDR rendering
Resource Manager
Lua Scripting
Impostor system
Tiled forward (Forward+) rendering (+2.5D culling)
Occlusion culling with gpu queries
Texture atlas packing
Tiled decals
Frame Profiler
Voxel Global Illumination
Reversed Z-buffer
Force Fields GPU simulation
Particle - Depth Buffer collisions
Translucent colored shadows
Refraction caustics
Local parallax-corrected environment maps
Volumetric light scattering
Smooth Particle Hydrodynamics (SPH) Fluid Simulation
Ray tracing, path tracing (on GPU)
Entity-Component System (Data oriented design)
Lightmap baking (with GPU path tracing)
Job system
Inverse Kinematics
Springs
HDR display output

GLTF 2.0 extensions supported:
KHR_materials_unlit
KHR_materials_transmission
KHR_materials_pbrSpecularGlossiness
KHR_materials_sheen
KHR_materials_clearcoat
KHR_materials_specular
KHR_materials_ior
KHR_texture_basisu
