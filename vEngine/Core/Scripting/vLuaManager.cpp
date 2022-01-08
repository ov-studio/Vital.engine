#include "Core/Scripting/vLuaBooter.h"

namespace wi::lua
{
    void AsyncUpdate()
    {
        Signal("vEngine_onAsyncUpdate");
    }

    void Update()
    {
        Signal("vEngine_onUpdate");
    }
    
    void Render()
    {
        Signal("vEngine_onRender");
    }
}