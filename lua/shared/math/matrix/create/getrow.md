---
description: Retrieves matrix's specified row.
---

# getRow

### ━ Syntax

<mark style="color:red;">**`[userdata rowVector] matrix:getRow(int rowIndex)`**</mark>

### ━ Usage

```lua
local cMatrix = vEngine.math.matrix.create(
    vEngine.math.vector.create(10, 10, 10, 10), --Row 0
    vEngine.math.vector.create(10, 10, 10, 10), --Row 1
    vEngine.math.vector.create(10, 10, 10, 10), --Row 2
    vEngine.math.vector.create(10, 10, 10, 10) --Row 3
)

local rowVector = cMatrix:getRow(1) --Retrieves our matrix's 1st row
print(rowVector) --Prints our row vector
```
