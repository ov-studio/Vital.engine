---
description: Sets colors's green channel value.
---

# setG

### ━ Syntax

<mark style="color:red;">**`[bool result] color:setG(int green)`**</mark>

### ━ Usage

```lua
local cColor = vEngine.color.create(0, 255, 0, 255) --Creates green color
local result = cColor:setG(0) --Updates green channel's value
print(result) --Prints result
```
