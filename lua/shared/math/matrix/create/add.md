---
description: Adds 2 matrixes.
---

# add

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] matrix:add(userdata matrix)`**</mark>

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

local resultantMatrix = cMatrix1:multiply(cMatrix2) --Adds our matrixes
print(resultantMatrix) --Prints our resultant matrix
```
