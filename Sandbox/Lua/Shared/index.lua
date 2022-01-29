----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: Shared: index.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Module Initializer ]]--
----------------------------------------------------------------


----------------
--[[ Module ]]--
----------------

vEngine.math.angle = {}

--Function: Prepares debug message
vEngine.prepareDebugMessage = function(API, messageType, message)
    if API and messageType and message then
        return "[API: "..tostring(API).."] | ["..tostring(messageType).."] "..tostring(message)
    end
    return ""
end
