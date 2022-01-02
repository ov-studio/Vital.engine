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