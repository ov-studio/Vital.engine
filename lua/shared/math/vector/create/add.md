---
description: Adds 2 vectors.
---

# add

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:add(userdata vector)`**</mark>

### ━ Usage

```lua
local cVector1 = vEngine.math.vector.create(10, 20, 30, 40) --Creates a new vector 1
local cVector2 = vEngine.math.vector.create(100, 200, 300, 400) --Creates a new vector 2
local resultantVector = cVector1:add(cVector2) --Adds our vectors
print(resultantVector) --Prints our resultant vector
```
