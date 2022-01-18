---
description: Transforms a vector's normal.
---

# transformNormal

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:transformNormal(userdata matrix)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector.create(10, 20, 30, 40) --Creates a new vector
local cMatrix = vEngine.math.matrix() --Creates a empty matrix
local resultantVector = cVector:transformNormal(cMatrix) --Transforms our vector's normal
print(resultantVector) --Prints our resultant vector
```
