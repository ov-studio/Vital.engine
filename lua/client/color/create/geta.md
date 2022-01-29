---
description: Retrieves colors's alpha channel value.
---

# getA

### ━ Syntax

<mark style="color:red;">**`[int value] color:getA()`**</mark>

### ━ Usage

```lua
local cColor = vEngine.color.create(255, 0, 0, 255) --Creates alpha color
local channelColor = cColor:getA() --Retrieves alpha channel's value
print(channelColor) --Prints our channel's value
```
