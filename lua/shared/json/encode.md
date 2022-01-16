---
description: Converts table to JSON.
---

# encode

### ━ Syntax

<mark style="color:red;">**`[json data] encode(table data)`**</mark>

### ━ Usage

```lua
--Data table to be converted
local myTable = {
    first = "first item",
    second = "second item"
}

local generatedJSON = vEngine.json.encode(myTable) --Converts our table to JSON
print(generatedJSON) --Prints generated JSON
```