---
description: Posts a message on the backlog.
---

# post

### ━ Syntax

<mark style="color:red;">**`[bool status] post(string message, int level)`**</mark>

### ━ Levels

* **0 - None**
* **1 - Default**
* **2 - Warning**
* **3 - Error**

### ━ Usage

```lua
local result = vEngine.backlog.post("Hello There", 1) --Posts our message on the backlog in default mode
print(result) --Prints result
```