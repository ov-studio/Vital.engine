---
description: Retrieves dot product of two vectors.
---

# dot

### ━ Syntax

<mark style="color:red;">**`[float product] vector:dot(userdata vector)`**</mark>

### ━ Usage

```lua
local cVector1 = vEngine.math.vector.create(10, 20, 30, 40) --Creates a new vector 1
local cVector2 = vEngine.math.vector.create(100, 200, 300, 400) --Creates a new vector 2
local vectorProduct = cVector1:dot(cVector2) --Retrieves dot product of our vectors
print(vectorProduct) --Prints our vector's product
```
