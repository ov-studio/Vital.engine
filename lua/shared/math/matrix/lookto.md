---
description: Creates a new matrix looking to a point.
---

# lookTo

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] lookAt(userdata eyeVector, userdata directionVector, userdata normalVector)`**</mark>

### ━ Usage

```lua
local eyeVector = vEngine.math.vector.create(10, 10, 10, 10) --Creates our eye vector
local directionVector = vEngine.math.vector.create(20, 30, 40, 0) --Creates our direction vector
local normalVector = vEngine.math.vector.create(0, 1, 0, 0) --Creates our normal vector

local cMatrix = vEngine.math.matrix.lookAt(eyeVector, directionVector, normalVector) --Creates our matrix
print(cMatrix) --Prints our matrix
```

### **━ Methods**

* [**Inherited from create**](create.md)