---
description: Multiplies 2 quaternion vectors.
---

# quatMultiply

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:quatMultiply(userdata vector)`**</mark>

### ━ Usage

```lua
local cVector1 = vEngine.math.vector(10, 20, 30, 40) --Creates a new vector 1
local cVector2 = vEngine.math.vector(100, 200, 300, 400) --Creates a new vector 2
local resultantVector = cVector1:quatMultiply(cVector2) --Multiplies our quaternion vector
print(resultantVector) --Prints our resultant vector
```
