---
description: Converts JSON to table.
---

# decode

### ━ Syntax

<mark style="color:red;">**`[table data] decode(json data)`**</mark>

### ━ Usage

```lua
--Data table to be converted
local myJSON = "[['first': 'first item', 'second': 'second item']]"

local generatedTable = vEngine.json.decode(myJSON) --Converts our JSON to table
print(generatedTable) --Prints generated Table
```