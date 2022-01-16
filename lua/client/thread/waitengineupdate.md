---
description: Awaits thread until the engine updates.
---

# waitEngineUpdate

### ━ Syntax

<mark style="color:red;">**`[bool status] waitEngineUpdate()`**</mark>

### ━ Usage

```lua
vEngine.thread.create(function() --Creates a new thread
    print("Hello") --Prints "Hello"
    vEngine.thread.waitEngineUpdate() --Waits for engine's update state
    print("There") --Prints "There"
end)
```