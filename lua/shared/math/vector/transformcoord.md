---
description: Transforms a vector's coord.
---

# transformCoord

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:transformCoord(userdata matrix)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector(10, 20, 30, 40) --Creates a new vector
local cMatrix = vEngine.math.matrix() --Creates a empty matrix
local resultantVector = cVector:transformCoord(cMatrix) --Transforms our vector's coord
print(resultantVector) --Prints our resultant vector
```
