---
description: Creates a new translation matrix.
---

# lookAt

### ━ Syntax

<mark style="color:red;">**`[userdata matrix] lookAt(userdata vector)`**</mark>

### ━ Usage

```lua
local cVector = vEngine.math.vector.lookAt(10, 10, 10, 10) --Creates our vector
local cMatrix = vEngine.math.vector.lookAt(cVector) --Creates our matrix
print(cMatrix) --Prints our matrix
```

### **━ Methods**

* [**Inherited from create**](create.md)