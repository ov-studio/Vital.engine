----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: Client: color.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Color Module ]]--
----------------------------------------------------------------


----------------
--[[ Module ]]--
----------------

--Function: Retrieves color from percentage
vEngine.color.fromPercent = function(percentage)
    local API = "vEngine.color.fromPercent"
    assert(not percentage or (type(percentage) ~= "number"), vEngine.postDebugMessage(API, "Invalid percentage", 3))

    percentage = vEngine.math.max(0, vEngine.math.min(100, percentage))
    local channelColors = {255, 255, 0, 255}
    channelColors = ((percentage > 50) and {(100 - percentage)*5.1, 255, 0, 255}) or ((percentage > 50) and {255, percentage*5.1, 0, 255}) or channelColors
    return vEngine.color.create(unpack(channelColors))
end