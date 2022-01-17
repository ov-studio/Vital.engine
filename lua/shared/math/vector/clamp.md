---
description: Clamps a vector.
---

# clamp

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:clamp(float minValue, float maxValue)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector(10, 20, 30, 40) --Creates a new vector
local resultantVector = cVector:clamp(100, 200) --Clamps our vector
print(resultantVector) --Prints our resultant vector
```
