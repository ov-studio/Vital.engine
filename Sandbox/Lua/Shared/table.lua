----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: Shared: table.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Table Module ]]--
----------------------------------------------------------------


----------------
--[[ Module ]]--
----------------

--Function: Clones a table
vEngine.table.clone = function(baseTable, isRecursive)
    local API = "vEngine.table.clone"
    assert(not baseTable or (type(baseTable) ~= "table"), vEngine.__postAPIMessage(API, "Invalid baseTable", 3))

    local clonedTable = {}
    for i, j in pairs(baseTable) do
        if (type(j) == "table") and isRecursive then
            clonedTable[i] = vEngine.table.clone(j, isRecursive)
        else
            clonedTable[i] = j
        end
    end
    return clonedTable
end
