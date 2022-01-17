---
description: Subtracts 2 vectors.
---

# subtract

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:subtract(userdata vector)`**</mark>

### ━ Usage

```lua
local cVector1 = vEngine.math.vector(10, 20, 30, 40) --Creates a new vector 1
local cVector2 = vEngine.math.vector(100, 200, 300, 400) --Creates a new vector 2
local resultantVector = cVector1:subtract(cVector2) --Subtracts our vector
print(resultantVector) --Prints our resultant vector
```
