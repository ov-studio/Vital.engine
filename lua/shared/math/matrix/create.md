---
description: Creates a new matrix.
---

# create

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] create(userdata rowVector1, userdata rowVector2, userdata rowVector3, userdata rowVector4)`**</mark>

### ━ Usage

```lua
--Creates our row vectors
local cVector1 = vEngine.math.vector.create(10, 10, 10, 10)
local cVector2 = vEngine.math.vector.create(100, 100, 100, 100)
local cVector3 = vEngine.math.vector.create(10, 10, 10, 10)
local cVector3 = vEngine.math.vector.create(100, 100, 100, 100)

--Creates matrix using row vectors
local cMatrix = vEngine.math.matrix.create(cVector1, cVector2, cVector3, cVector4)
print(cMatrix) --Prints our matrix
```

### **━ Methods**
