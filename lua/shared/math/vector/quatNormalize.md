---
description: Normalizes a quaternion vector.
---

# quatNormalize

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:quatNormalize()`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector(10, 20, 30, 40) --Creates a new vector
local resultantVector = cVector:quatNormalize() --Normalizes our quaternion vector
print(resultantVector) --Prints our resultant vector
```
