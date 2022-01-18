---
description: Transforms a vector.
---

# transform

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:transform(userdata matrix)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector.create(10, 20, 30, 40) --Creates a new vector
local cMatrix = vEngine.math.matrix() --Creates a empty matrix
local resultantVector = cVector:transform(cMatrix) --Transforms our vector
print(resultantVector) --Prints our resultant vector
```
