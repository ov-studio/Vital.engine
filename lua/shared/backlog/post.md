---
description: Posts a message on the backlog.
---

# post

### ━ Syntax

<mark style="color:red;">**`[bool status] post(string message, int level)`**</mark>

* [**Backlog Levels**](./)

### ━ Usage

```lua
local result = vEngine.backlog.post("Hello There", 1) --Posts our message on the backlog in default mode
print(result) --Prints result
```
