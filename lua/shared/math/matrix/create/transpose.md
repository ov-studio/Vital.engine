---
description: Adds 2 matrixes.
---

# transpose

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] matrix:transpose(userdata matrix)`**</mark>

### ━ Usage

```lua
local cMatrix = vEngine.math.matrix.create(
    vEngine.math.vector.create(10, 10, 10, 10),
    vEngine.math.vector.create(10, 10, 10, 10),
    vEngine.math.vector.create(10, 10, 10, 10),
    vEngine.math.vector.create(10, 10, 10, 10)
)

local resultantMatrix = cMatrix:transpose() --Retrieves our matrix's transpose
print(resultantMatrix) --Prints our resultant matrix
```
