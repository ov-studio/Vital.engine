---
description: Sets vector's w coord.
---

# setW

### ━ Syntax

<mark style="color:red;">**`[bool status] vector:setW(float w)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector.create(10, 20, 30, 40) --Creates a new vector
local result = cVector:setW(500) --Retrieves vector's w coord
print(result) --Prints result
```
