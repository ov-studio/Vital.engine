---
description: Retrieves quaternion vector from position & rotation vector.
---

# quatFromRollPitchYaw

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:quatFromRollPitchYaw()`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector.create(10, 20, 30, 40) --Creates a new position vector
local resultantVector = cVector:quatFromRollPitchYaw() --Retrieves our quaternion vector
print(resultantVector) --Prints our resultant vector
```
