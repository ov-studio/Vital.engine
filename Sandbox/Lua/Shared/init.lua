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

vEngine.math = math; math = nil;
vEngine.math.angle = {}
vEngine.string = string; string = nil;
vEngine.json = json; json = nil;
vEngine.color = {}

--Function: Prepares debug message
vEngine.prepareDebugMessage = function(interface, API, messageType, message)
    if interface and API and messageType and message then
        return "["..tostring(interface).."] [API: "..tostring(API).."] | ["..tostring(messageType).."] "..tostring(message)
    end
    return ""
end
