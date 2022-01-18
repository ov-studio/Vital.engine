---
description: Retrieves inverse of a matrix.
---

# inverse

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] matrix:inverse()`**</mark>

### ━ Usage

```lua
local cVector1 = vEngine.math.matrix.create(10, 20, 30, 40) --Creates a new matrix 1
local cVector2 = vEngine.math.matrix.create(100, 200, 300, 400) --Creates a new matrix 2
local resultantMatrix = cVector1:inverse(cVector2) --Adds our matrixes
print(resultantMatrix) --Prints our resultant matrix
```
