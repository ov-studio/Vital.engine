---
description: Retrieves quaternion vector from position & rotation vector.
---

# quatFromRollPitchYaw

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:quatFromRollPitchYaw(userdata rotVector)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector(10, 20, 30, 40) --Creates a new position vector
local rotVector = vEngine.math.vector(100, 60, 10, 150) --Creates a new rotation vector
local resultantVector = cVector:quatFromRollPitchYaw(rotVector) --Retrieves our quaternion vector
print(resultantVector) --Prints our resultant vector
```
