---
description: Creates a new rotation matrix.
---

# rotation

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] rotation(userdata vector)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector.create(10, 10, 10, 10) --Creates our vector
local cMatrix = vEngine.math.matrix.rotation(cVector) --Creates our matrix
print(cMatrix) --Prints our matrix
```

### **━ Methods**

* [**Inherited from create**](create.md)