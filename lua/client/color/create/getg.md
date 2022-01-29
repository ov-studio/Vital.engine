---
description: Retrieves colors's green channel value.
---

# getG

### ━ Syntax

<mark style="color:red;">**`[int value] color:getG()`**</mark>

### ━ Usage

```lua
local cColor = vEngine.color.create(255, 0, 0, 255) --Creates green color
local channelColor = cColor:getG() --Retrieves green channel's value
print(channelColor) --Prints our channel's value
```
