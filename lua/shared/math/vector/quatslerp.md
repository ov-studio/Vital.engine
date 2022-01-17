---
description: Slerps a quaternion vector.
---

# quatSlerp

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:quatSlerp(userdata vector, float lerpRate)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector(10, 20, 30, 40) --Creates a new vector
local resultantVector = cVector:quatSlerp(vEngine.math.vector(1, 2, 1, 5), 0.5) --Slerps our quaternion vector
print(resultantVector) --Prints our resultant vector
```
