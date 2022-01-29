---
description: Sets colors's red channel value.
---

# setR

### ━ Syntax

<mark style="color:red;">**`[bool result] color:setR(int red)`**</mark>

### ━ Usage

```lua
local cColor = vEngine.color.create(255, 0, 0, 255) --Creates red color
local result = cColor:setR(0) --Updates red channel's value
print(result) --Prints result
```
