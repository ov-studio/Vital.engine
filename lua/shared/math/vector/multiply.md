---
description: Multiplies 2 vectors.
---

# multiply

### ━ Syntax

<mark style="color:red;">**`[userdata vector] vector:multiply([userdata vector, float multiplier])`**</mark>

### ━ Usage

```lua
--Syntax 1:
local cVector1 = vEngine.math.vector(10, 20, 30, 40) --Creates a new vector 1
local cVector2 = vEngine.math.vector(100, 200, 300, 400) --Creates a new vector 2
local resultantVector = cVector1:multiply(cVector2) --Multiplies our vector
print(resultantVector) --Prints our resultant vector

--Syntax 2:
local cVector = vEngine.math.vector(10, 20, 30, 40) --Creates a new vector
local vectorMultiplier = 5
local resultantVector = cVector1:multiply(cVector, vectorMultiplier) --Multiplies our vector
print(resultantVector) --Prints our resultant vector
```
