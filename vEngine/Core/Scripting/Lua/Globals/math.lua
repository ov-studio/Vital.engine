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
vEngine.math.randomseed(os.time()); os = nil;

--Function: Lerps a number linearlly
vEngine.math.lerp = function(minValue, maxValue, lerpRate)
    local API_REF = "vEngine.math.lerp"
    assert(not minValue or (type(minValue) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid lerp minValue")
    assert(not maxValue or (type(maxValue) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid lerp maxValue")
    assert(not lerpRate or (type(lerpRate) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid lerpRate")
	return minValue + ((maxValue - minValue)*lerpRate)
end

--Function: Clamps a number
vEngine.math.clamp = function(value, min, max)
    local API_REF = "vEngine.math.clamp"
    assert(not value or (type(value) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid clamping value")
    assert(not min or (type(min) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid clamping minValue")
    assert(not max or (type(max) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid clamping maxValue")
    return ((value < min) and min) or ((value > max) and max) or value
end

--Function: Saturates a number
vEngine.math.saturate = function(value)
    local API_REF = "vEngine.math.saturate"
    assert(not value or (type(value) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid saturation value")
	return vEngine.math.clamp(value, 0, 1)
end

--Function: Rounds a number
vEngine.math.round = function(value, decimals)
    local API_REF = "vEngine.math.round"
    assert(not value or (type(value) ~= "number"), "[API: "..API_REF.."] | [Error] Invalid rounding value")
    decimals = tonumber(decimals) or 0
    assert(not decimals or (type(decimals) < 0), "[API: "..API_REF.."] | [Error] Invalid rounding decimals")
    return tonumber(string.format(("%."..decimals.."f"), value))
end