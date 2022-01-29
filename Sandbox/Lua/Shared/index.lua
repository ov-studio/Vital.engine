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

--Function: Posts debug message
vEngine.postDebugMessage = function(API, message, messageLevel)
    messageLevel = tonumber(messageLevel)
    if messageLevel and message then
        message = ((API and "[API: "..tostring(API).."] | ") or "")..tostring(message)
        return vEngine.backlog:post(message, messageLevel)
    end
    return false
end
