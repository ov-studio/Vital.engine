---
description: Retrieves colors's red channel value.
---

# getR

### ━ Syntax

<mark style="color:red;">**`[int value] color:getR()`**</mark>

### ━ Usage

```lua
local cColor = vEngine.color.create(255, 0, 0, 255) --Creates red color
local channelColor = cColor:getR() --Retrieves red channel's value
print(channelColor) --Prints our channel's value
```
