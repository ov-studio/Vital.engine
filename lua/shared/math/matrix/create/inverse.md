---
description: Retrieves inverse of a matrix.
---

# inverse

### ━ Syntax

<mark style="color:red;">**`[userdata matrix, float determinant] matrix:inverse()`**</mark>

### ━ Usage

```lua
local cMatrix = vEngine.math.matrix.create(
    vEngine.math.vector.create(10, 10, 10, 10),
    vEngine.math.vector.create(10, 10, 10, 10),
    vEngine.math.vector.create(10, 10, 10, 10),
    vEngine.math.vector.create(10, 10, 10, 10)
)

local resultantMatrix, resultantDeterminant = cMatrix:transpose() --Retrieves our matrix's inverse & determinant

--Prints our resultant matrix & determinant
print(resultantMatrix)
print(resultantDeterminant)
```
