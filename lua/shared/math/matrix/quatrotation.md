---
description: Creates a new quaternion rotation matrix.
---

# quatRotation

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] quatRotation(userdata vector)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector.create(10, 10, 10, 10) --Creates our vector
local cMatrix = vEngine.math.vector.quatRotation(cVector) --Creates our matrix
print(cMatrix) --Prints our matrix
```

### **━ Methods**

* [**Inherited from create**](create.md)