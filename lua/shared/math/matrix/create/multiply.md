---
description: Multiplies 2 matrixes.
---

# multiply

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] matrix:multiply(userdata matrix)`**</mark>

### ━ Usage

```lua
local cMatrix1 = vEngine.math.matrix.create(
    vEngine.math.vector.create(10, 10, 10, 10),
    vEngine.math.vector.create(10, 10, 10, 10),
    vEngine.math.vector.create(10, 10, 10, 10),
    vEngine.math.vector.create(10, 10, 10, 10)
)
local cMatrix2 = vEngine.math.matrix.create(
    vEngine.math.vector.create(100, 100, 100, 100),
    vEngine.math.vector.create(100, 100, 100, 100),
    vEngine.math.vector.create(100, 100, 100, 100),
    vEngine.math.vector.create(100, 100, 100, 100)
)

local resultantMatrix = cMatrix1:multiply(cMatrix2) --Multiplies our matrixes
print(resultantMatrix) --Prints our resultant matrix
```
