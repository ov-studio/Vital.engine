----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: Shared: math.lua
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
    assert(not minValue or (type(minValue) ~= "number"), vEngine.postDebugMessage(API, "Invalid minValue", 3))
    assert(not maxValue or (type(maxValue) ~= "number"), vEngine.postDebugMessage(API, "Invalid maxValue", 3))
    assert(not lerpRate or (type(lerpRate) ~= "number"), vEngine.postDebugMessage(API, "Invalid lerpRate", 3))

    return minValue + ((maxValue - minValue)*lerpRate)
end

--Function: Clamps a number
vEngine.math.clamp = function(value, minValue, maxValue)
    local API = "vEngine.math.clamp"
    assert(not value or (type(value) ~= "number"), vEngine.postDebugMessage(API, "Invalid value", 3))
    assert(not minValue or (type(minValue) ~= "number"), vEngine.postDebugMessage(API, "Invalid minValue", 3))
    assert(not maxValue or (type(maxValue) ~= "number"), vEngine.postDebugMessage(API, "Invalid maxValue", 3))

    return ((value < minValue) and minValue) or ((value > maxValue) and maxValue) or value
end

--Function: Saturates a number
vEngine.math.saturate = function(value)
    local API = "vEngine.math.saturate"
    assert(not value or (type(value) ~= "number"), vEngine.postDebugMessage(API, "Invalid value", 3))

    return vEngine.math.clamp(value, 0, 1)
end

--Function: Rounds a number
vEngine.math.round = function(value, decimals)
    local API = "vEngine.math.round"
    assert(not value or (type(value) ~= "number"), vEngine.postDebugMessage(API, "Invalid value", 3))
    decimals = tonumber(decimals) or 0
    assert(not decimals or (type(decimals) < 0), vEngine.postDebugMessage(API, "Invalid decimals", 3))

    return tonumber(vEngine.string.format(("%."..decimals.."f"), value))
end

--Function: Retrieves progress of a tick
vEngine.math.tickProgress = function(tick, duration)
    local API = "vEngine.math.progress"
    assert(not tick or (type(tick) ~= "number"), vEngine.postDebugMessage(API, "Invalid tick", 3))
    assert(not duration or (type(duration) ~= "number") or (duration <= 0), vEngine.postDebugMessage(API, "Invalid duration", 3))

    local endTick = tick + duration
    return (vEngine.thread.getTick() - tick)/(endTick - tick)
end

--Function: Retrieves percentage of a number
vEngine.math.percent = function(value, percentage)
    local API = "vEngine.math.percent"
    assert(not value or (type(value) ~= "number"), vEngine.postDebugMessage(API, "Invalid value", 3))
    assert(not percentage or (type(percentage) ~= "number"), vEngine.postDebugMessage(API, "Invalid percentage", 3))

    return (value*percentage)/100
end

--Function: Retrieves shortest target angle
vEngine.math.angle.shortTarget = function(initialAngle, finalAngle)
    local API = "vEngine.math.angle.shortTarget"
    assert(not initialAngle or (type(initialAngle) ~= "number"), vEngine.postDebugMessage(API, "Invalid initialAngle", 3))
    assert(not finalAngle or (type(finalAngle) ~= "number"), vEngine.postDebugMessage(API, "Invalid finalAngle", 3))

    local shortestAngle = ((initialAngle < finalAngle) and (finalAngle - initialAngle)) or (initialAngle - finalAngle)
    return vEngine.math.min(shortestAngle, 360 - shortestAngle)
end

--Function: Retrieves rotation angle in 2D
vEngine.math.angle.rotationAngle2D = function(startX, startY, endX, endY) 
    local API = "vEngine.math.angle.rotationAngle2D"
    assert(not startX or (type(startX) ~= "number"), vEngine.postDebugMessage(API, "Invalid startX", 3))
    assert(not startY or (type(startY) ~= "number"), vEngine.postDebugMessage(API, "Invalid startY", 3))
    assert(not endX or (type(endX) ~= "number"), vEngine.postDebugMessage(API, "Invalid endX", 3))
    assert(not endY or (type(endY) ~= "number"), vEngine.postDebugMessage(API, "Invalid endY", 3))

    local rotationAngle = -vEngine.math.deg(vEngine.math.atan2(endX - startX, endY - startY))
    return ((rotationAngle < 0) and (rotationAngle + 360)) or rotationAngle
end