---
description: Saturates a vector.
---

# saturate

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:saturate()`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector.create(10, 20, 30, 40) --Creates a new vector
local resultantVector = cVector:saturate() --Saturates our vector
print(resultantVector) --Prints our resultant vector
```
