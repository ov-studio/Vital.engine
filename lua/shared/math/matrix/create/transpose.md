---
description: Retrieves transpose of a matrix.
---

# transpose

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] matrix:transpose()`**</mark>

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
