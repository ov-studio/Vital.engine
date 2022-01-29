---
description: Retrieves colors's blue channel value.
---

# getB

### ━ Syntax

<mark style="color:red;">**`[int value] color:getB()`**</mark>

### ━ Usage

```lua
local cColor = vEngine.color.create(255, 0, 0, 255) --Creates blue color
local channelColor = cColor:getB() --Retrieves blue channel's value
print(channelColor) --Prints our channel's value
```
