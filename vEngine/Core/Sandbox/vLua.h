#include "Core/Helpers/wiVector.h"
#include <string>
namespace sandbox {}
namespace sandbox::lua {
struct moduleDef
{
    std::string moduleName;
    wi::vector<std::string> moduleScripts;
};

wi::vector<moduleDef> modules = {
{
"Shared",
{
R"(
----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: init.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Module Initializer ]]--
----------------------------------------------------------------


----------------
--[[ Module ]]--
----------------

vEngine = {}
vEngine.math = math; math = nil;
vEngine.math.angle = {}
vEngine.string = string; string = nil;
vEngine.color = {}

--Function: Prepares debug message
vEngine.prepareDebugMessage = function(interface, API, messageType, message)
    if interface and API and messageType and message then
        return "["..tostring(interface).."] [API: "..tostring(API).."] | ["..tostring(messageType).."] "..tostring(message)
    end
    return ""
end
)",
R"(
----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: math.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Math Module ]]--
----------------------------------------------------------------


----------------
--[[ Module ]]--
----------------

--Function: Lerps a number linearly
vEngine.math.lerp = function(minValue, maxValue, lerpRate)
    local API = "vEngine.math.lerp"
    assert(not minValue or (type(minValue) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid minValue"))
    assert(not maxValue or (type(maxValue) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid maxValue"))
    assert(not lerpRate or (type(lerpRate) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid lerpRate"))

	return minValue + ((maxValue - minValue)*lerpRate)
end

--Function: Clamps a number
vEngine.math.clamp = function(value, minValue, maxValue)
    local API = "vEngine.math.clamp"
    assert(not value or (type(value) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid value"))
    assert(not minValue or (type(minValue) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid minValue"))
    assert(not maxValue or (type(maxValue) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid maxValue"))

    return ((value < minValue) and minValue) or ((value > maxValue) and maxValue) or value
end

--Function: Saturates a number
vEngine.math.saturate = function(value)
    local API = "vEngine.math.saturate"
    assert(not value or (type(value) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid value"))

	return vEngine.math.clamp(value, 0, 1)
end

--Function: Rounds a number
vEngine.math.round = function(value, decimals)
    local API = "vEngine.math.round"
    assert(not value or (type(value) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid value"))
    decimals = tonumber(decimals) or 0
    assert(not decimals or (type(decimals) < 0), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid decimals"))

    return tonumber(vEngine.string.format(("%."..decimals.."f"), value))
end

--Function: Retrieves progress of a tick
vEngine.math.tickProgress = function(tick, duration)
    local API = "vEngine.math.progress"
    assert(not tick or (type(tick) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid tick"))
    assert(not duration or (type(duration) ~= "number") or (duration <= 0), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid duration"))

    local endTick = tick + duration
    return (vEngine.thread.getTick() - tick)/(endTick - tick)
end

--Function: Retrieves percentage of a number
vEngine.math.percent = function(value, percentage)
    local API = "vEngine.math.percent"
    assert(not value or (type(value) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid value"))
    assert(not percentage or (type(percentage) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid percentage"))

    return (value*percentage)/100
end

--Function: Retrieves shortest target angle
vEngine.math.angle.shortTarget = function(initialAngle, finalAngle)
    local API = "vEngine.math.angle.shortTarget"
    assert(not initialAngle or (type(initialAngle) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid initialAngle"))
    assert(not finalAngle or (type(finalAngle) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid finalAngle"))

    local shortestAngle = ((initialAngle < finalAngle) and (finalAngle - initialAngle)) or (initialAngle - finalAngle)
    return vEngine.math.min(shortestAngle, 360 - shortestAngle)
end

--Function: Retrieves rotation angle in 2D
vEngine.math.angle.rotationAngle2D = function(startX, startY, endX, endY) 
    local API = "vEngine.math.angle.rotationAngle2D"
    assert(not startX or (type(startX) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid startX"))
    assert(not startY or (type(startY) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid startY"))
    assert(not endX or (type(endX) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid endX"))
    assert(not endY or (type(endY) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid endY"))

    local rotationAngle = -vEngine.math.deg(vEngine.math.atan2(endX - startX, endY - startY))
    return ((rotationAngle < 0) and (rotationAngle + 360)) or rotationAngle
end
)",
R"(
----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: color.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Color Module ]]--
----------------------------------------------------------------


----------------
--[[ Module ]]--
----------------

--Function: Retrieves color from RGBA
vEngine.color.fromRGBA = function(red, green, blue, alpha)
    local API = "vEngine.color.fromRGBA"
    assert(not red or (type(red) ~= "number") or (red < 0) or (red > 255), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid red channel value"))
    assert(not green or (type(green) ~= "number") or (green < 0) or (green > 255), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid green channel value"))
    assert(not blue or (type(blue) ~= "number") or (blue < 0) or (blue > 255), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid blue channel value"))
    alpha = vEngine.math.max(0, vEngine.math.min(255, tonumber(alpha) or 0))

    --TODO: CREATE COLOR VIA PIPELINE & return
    --return toColor(red, green, blue, alpha)
end

--Function: Retrieves color from percentage
vEngine.color.fromPercent = function(percentage)
    local API = "vEngine.color.fromPercent"
    assert(not percentage or (type(percentage) ~= "number"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid percentage"))

    local channelColors = false
    percentage = vEngine.math.max(0, vEngine.math.min(100, percentage))
    if percentage > 50 then
        channelColors = {(100 - percentage)*5.1, 255, 0, 255}
    elseif percentage == 50 then
        channelColors = {255, 255, 0, 255}
    else
        channelColors = {255, percentage*5.1, 0, 255}
    end
    --TODO: CREATE COLOR VIA PIPELINE & return
    --return toColor(red, green, blue, alpha)
end
)",
}
},
{
"Client",
{
R"(
----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: thread.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Thread Module ]]--
----------------------------------------------------------------


---------------
--[[ Cache ]]--
---------------

local cache = {
    timedThreads = {},
    signaledThreads = {},
    currentTick = 0
}

cache.waitSignal = function(signalType)
    local API = "vEngine.thread.wait"
    local cThread = coroutine.running()
    assert(not cThread, vEngine.prepareDebugMessage("LUA", API, "Error", "API available only within a thread"))

    cache.signaledThreads[signalType] = cache.signaledThreads[signalType] or {}
    table.insert(cache.signaledThreads[signalType], cThread)
    return coroutine.yield()
end

function onvEngineSignal(signalType)
    if signalType == "vEngine_onRender" then
        for i, j in pairs(cache.timedThreads) do
            if j < cache.currentTick then
                coroutine.resume(j)
                cache.timedThreads[i] = nil
            end
        end
        cache.currentTick = cache.currentTick + 1
    end
    if not cache.signaledThreads[signalType] then return false end

    for i, j in ipairs(cache.signaledThreads[signalType]) do
        coroutine.resume(j)
    end
    cache.signaledThreads[signalType] = nil
    return true
end


----------------
--[[ Module ]]--
----------------

vEngine.thread = {}

--Function: Retrieves current tick
vEngine.thread.getTick = function()
    return cache.currentTick
end

--Function: Creates a thread
vEngine.thread.create = function(cHandler)
    local API = "vEngine.thread.create"
    assert(not cHandler or (type(cHandler) ~= "function"), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid thread handler"))

    local cThread = coroutine.create(cHandler)
    local cResult = {coroutine.resume(cThread)}
    assert(not cResult[1], vEngine.prepareDebugMessage("LUA", API, "Error", cResult[2]))
    return cThread
end

--Function: Destroys all threads
vEngine.thread.destroyAll = function()
    cache.signaledThreads = {}
    cache.timedThreads = {}
    return true
end

--Function: awaits thread for 'n' duration before running again
vEngine.thread.wait = function(duration)
    local API = "vEngine.thread.wait"
    assert(not duration or (type(duration) ~= "number") or (duration <= 0), vEngine.prepareDebugMessage("LUA", API, "Error", "Invalid duration"))
    local cThread = coroutine.running()
    assert(not cThread, vEngine.prepareDebugMessage("LUA", API, "Error", "API available only within a thread"))

    cache.timedThreads[cThread] = cache.currentTick + duration
    return coroutine.yield(cThread)
end

--Function: awaits thread until the engine updates
vEngine.thread.waitEngineUpdate = function()
    cache.waitSignal("vEngine_onUpdate")
end

--Function: awaits thread until the engine updates independent of the frame
vEngine.thread.waitEngineAsyncUpdate = function()
    cache.waitSignal("vEngine_onAsyncUpdate")
end

--Function: awaits thread until the engine renders
vEngine.thread.waitEngineRender = function()
    cache.waitSignal("vEngine_onRender")
end

)",
}
},
{
"Server",
{
}
},
};
};
