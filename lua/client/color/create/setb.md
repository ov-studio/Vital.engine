---
description: Sets colors's blue channel value.
---

# setB

### ━ Syntax

<mark style="color:red;">**`[bool result] color:setB(int blue)`**</mark>

### ━ Usage

```lua
local cColor = vEngine.color.create(0, 0, 255, 255) --Creates blue color
local result = cColor:setB(0) --Updates blue channel's value
print(result) --Prints result
```
