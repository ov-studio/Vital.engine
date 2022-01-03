----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: thread.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Thread Module ]]--
----------------------------------------------------------------


---------------
--[[ Cacje ]]--
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
vEngine.thread.waitEngineFixedUpdate = function()
    cache.waitSignal("vEngine_onAsyncUpdate")
end

--Function: awaits thread until the engine renders
vEngine.thread.waitEngineRender = function()
    cache.waitSignal("vEngine_onRender")
end