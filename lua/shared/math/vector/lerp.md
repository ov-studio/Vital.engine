---
description: Lerps a vector.
---

# lerp

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:lerp(userdata vector, float lerpRate)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector(10, 20, 30, 40) --Creates a new vector
local resultantVector = cVector:lerp(vEngine.math.vector(1, 2, 1, 5), 0.5) --Lerps our vector
print(resultantVector) --Prints our resultant vector
```
