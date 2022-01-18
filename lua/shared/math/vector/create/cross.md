---
description: Retrieves cross product of two vectors.
---

# cross

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:cross(userdata vector)`**</mark>

### ━ Usage

```lua
local cVector1 = vEngine.math.vector.create(10, 20, 30, 40) --Creates a new vector 1
local cVector2 = vEngine.math.vector.create(100, 200, 300, 400) --Creates a new vector 2
local vectorProduct = cVector1:cross(cVector2) --Retrieves cross product of our vectors
print(vectorProduct) --Prints our vector's product
```
