----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: generic.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Math Module ]]--
----------------------------------------------------------------


----------------
--[[ Module ]]--
----------------

vEngine.math = math; math = nil;
vEngine.math.angle = {}
vEngine.math.randomseed(os.time()); os = nil;

--Function: Lerps a number linearly
vEngine.math.lerp = function(minValue, maxValue, lerpRate)
    local API_REF = "vEngine.math.lerp"
    assert(not minValue or (type(minValue) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid minValue")
    assert(not maxValue or (type(maxValue) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid maxValue")
    assert(not lerpRate or (type(lerpRate) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid lerpRate")

	return minValue + ((maxValue - minValue)*lerpRate)
end

--Function: Clamps a number
vEngine.math.clamp = function(value, min, max)
    local API_REF = "vEngine.math.clamp"
    assert(not value or (type(value) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid value")
    assert(not min or (type(min) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid minValue")
    assert(not max or (type(max) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid maxValue")

    return ((value < min) and min) or ((value > max) and max) or value
end

--Function: Saturates a number
vEngine.math.saturate = function(value)
    local API_REF = "vEngine.math.saturate"
    assert(not value or (type(value) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid value")

	return vEngine.math.clamp(value, 0, 1)
end

--Function: Rounds a number
vEngine.math.round = function(value, decimals)
    local API_REF = "vEngine.math.round"
    assert(not value or (type(value) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid value")
    decimals = tonumber(decimals) or 0
    assert(not decimals or (type(decimals) < 0), "[API: "..API_REF.."] | [Error] Invalid decimals")

    return tonumber(string.format(("%."..decimals.."f"), value))
end

--Function: Retrieves percent of a number
vEngine.math.percent = function(value, percentage)
    local API_REF = "vEngine.math.percent"
    assert(not value or (type(value) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid value")
    assert(not percentage or (type(percentage) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid percentage")

    return (value*percentage)/100
end

--Function: Retrieves shortest target angle
vEngine.math.angle.shortTarget = function(initialAngle, finalAngle)
    local API_REF = "vEngine.math.angle.shortTarget"
    assert(not initialAngle or (type(initialAngle) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid initialAngle")
    assert(not finalAngle or (type(finalAngle) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid finalAngle")

    local shortestAngle = ((initialAngle < finalAngle) and (finalAngle - initialAngle)) or (initialAngle - finalAngle)
    return vEngine.math.min(shortestAngle, 360 - shortestAngle)
end

--Function: Retrieves rotation angle in 2D
vEngine.math.angle.rotationAngle2D = function(startX, startY, endX, endY) 
    local API_REF = "vEngine.math.angle.rotationAngle2D"
    assert(not startX or (type(startX) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid startX")
    assert(not startY or (type(startY) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid startY")
    assert(not endX or (type(endX) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid endX")
    assert(not endY or (type(endY) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid endY")

    local rotationAngle = -vEngine.math.deg(vEngine.math.atan2(endX - startX, endY - startY))
    return ((rotationAngle < 0) and (rotationAngle + 360)) or rotationAngle
end