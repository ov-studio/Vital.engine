---
description: Posts a message on the backlog.
---

# post

### ━ Syntax

<mark style="color:red;">**`[bool status] post(string message, int level)`**</mark>

* [<mark style="color:green;">**Backlog Levels**</mark>](./)<mark style="color:green;"></mark>

### ━ Usage

```lua
local result = vEngine.backlog.post("Hello There", 1) --Posts our message on the backlog in default mode
print(result) --Prints result
```
