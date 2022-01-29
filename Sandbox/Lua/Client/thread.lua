----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: Client: thread.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Thread Module ]]--
----------------------------------------------------------------


---------------
--[[ Cache ]]--
---------------

local cache = {
    coroutine = coroutine,
    timedThreads = {},
    signaledThreads = {},
    currentTick = 0
}
coroutine = nil

cache.waitSignal = function(signalType)
    local API = "vEngine.thread.wait"
    local cThread = cache.coroutine.running()
    assert(not cThread, vEngine.prepareDebugMessage(API, "Error", "API available only within a thread"))

    cache.signaledThreads[signalType] = cache.signaledThreads[signalType] or {}
    table.insert(cache.signaledThreads[signalType], cThread)
    return cache.coroutine.yield()
end

function onvEngineSignal(signalType)
    if signalType == "vEngine_onRender" then
        for i, j in pairs(cache.timedThreads) do
            if j < cache.currentTick then
                cache.coroutine.resume(j)
                cache.timedThreads[i] = nil
            end
        end
        cache.currentTick = cache.currentTick + 1
    end
    if not cache.signaledThreads[signalType] then return false end

    for i, j in ipairs(cache.signaledThreads[signalType]) do
        cache.coroutine.resume(j)
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
    assert(not cHandler or (type(cHandler) ~= "function"), vEngine.prepareDebugMessage(API, "Error", "Invalid thread handler"))

    local cThread = cache.coroutine.create(cHandler)
    local cResult = {cache.coroutine.resume(cThread)}
    assert(not cResult[1], vEngine.prepareDebugMessage(API, "Error", cResult[2]))
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
    assert(not duration or (type(duration) ~= "number") or (duration <= 0), vEngine.prepareDebugMessage(API, "Error", "Invalid duration"))
    local cThread = cache.coroutine.running()
    assert(not cThread, vEngine.prepareDebugMessage(API, "Error", "API available only within a thread"))

    cache.timedThreads[cThread] = cache.currentTick + duration
    return cache.coroutine.yield(cThread)
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
