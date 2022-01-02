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
    onSignal = {},
    onTime = {}
}


----------------
--[[ Module ]]--
----------------

vEngine.threads = {
    --Function: Creates a Thread
    create = function(threadFunc)
        assert(not threadFunc or (type(threadFunc) ~= "function"), "[API: vEngine.threads.create] | [Error] Invalid function handler")

        local createdThread = coroutine.create(threadFunc)
        local success, errorMsg = coroutine.resume(createdThread)
        if not success then
            error("[Lua Error] "..errorMsg)
        end
        return createdThread
    end,

    --Function: Destroys All Threads
    destroyThreads = function()
        cache.onSignal = {}
        cache.onTime = {}
    end,

    --Function: Wait 'n' seconds before running again
    waitSeconds = function(seconds)
        seconds = tonumber(seconds) or 0
        assert(seconds <= 0, "[API: vEngine.threads.waitSeconds] | [Error] Invalid duration")
        local cThread = coroutine.running()
        assert(cThread ~= nil, "[API: vEngine.threads.waitSeconds] | [Error] You can't await main thread!")
        
        local wakeupTime = CURRENT_TIME + seconds
        cache.onTime[cThread] = wakeupTime
        return coroutine.yield(cThread)
    end,

    --Function: Wait until the game updates dependent of the frame
    waitEngineUpdate = function()
        waitSignal("vEngine_onUpdate")
    end,

    --Function: Wait until the game updates independent of the frame
    waitEngineFixedUpdate = function()
        waitSignal("vEngine_onAsyncUpdate")
    end,

    --Function: Wait until the game is renderered
    waitEngineRender = function()
        waitSignal("vEngine_onRender")
    end
}



-- Store the delta time for the current frame
local lastDeltaTime = 0
function setDeltaTime(dt)
	lastDeltaTime = dt
	wakeUpWaitingThreads(dt)
end
function getDeltaTime()
	return lastDeltaTime
end


-- Keep track of how long the game has been running.
local CURRENT_TIME = 0

-- This function should be called once per game logic update with the amount of time
-- that has passed since it was last called
function wakeUpWaitingThreads(deltaTime)  
    CURRENT_TIME = CURRENT_TIME + deltaTime

    -- First, grab a list of the threads that need to be woken up. They'll need to be removed
    -- from the cache.onTime table which we don't want to try and do while we're iterating
    -- through that table, hence the list.
    local threadsToWake = {}
    for cThread, wakeupTime in pairs(cache.onTime) do
        if wakeupTime < CURRENT_TIME then
            table.insert(threadsToWake, cThread)
        end
    end

    -- Now wake them all up.
    for _, cThread in ipairs(threadsToWake) do
        cache.onTime[cThread] = nil -- Setting a field to nil removes it from the table
        local success, errorMsg = coroutine.resume(cThread)
		if not success then
			error("[Lua Error] "..errorMsg)
		end
    end
end

-- Block coroutine while waiting for a signal
function waitSignal(signalName)
    -- Same check as in waitSeconds; the main thread cannot wait
    local cThread = coroutine.running()
    assert(cThread ~= nil, "The main thread cannot wait!")

    if cache.onSignal[signalName] == nil then
        -- If there wasn't already a list for this signal, start a new one.
        cache.onSignal[signalName] = { cThread }
    else
        table.insert(cache.onSignal[signalName], cThread)
    end
    return coroutine.yield()
end

-- Send a signal on which a coroutine can be blocked
function signal(signalName)  
    local threads = cache.onSignal[signalName]
    if threads == nil then return end

    cache.onSignal[signalName] = nil
    for _, cThread in ipairs(threads) do
        local success, errorMsg = coroutine.resume(cThread)
		if not success then
			error("[Lua Error] "..errorMsg)
		end
    end
end