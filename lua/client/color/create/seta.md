---
description: Sets colors's alpha channel value.
---

# setA

### ━ Syntax

<mark style="color:red;">**`[bool result] color:setA(int alpha)`**</mark>

### ━ Usage

```lua
local cColor = vEngine.color.create(255, 255, 255, 255) --Creates white opaque color
local result = cColor:setA(0) --Updates alpha channel's value
print(result) --Prints result
```
