---
description: Awaits thread until the engine updates independent of the frame.
---

# waitEngineAsyncUpdate

### ━ Syntax

<mark style="color:red;">**`[bool status] waitEngineAsyncUpdate()`**</mark>

### ━ Usage

```lua
vEngine.thread.create(function() --Creates a new thread
    print("Hello") --Prints "Hello"
    vEngine.thread.waitEngineAsyncUpdate() --Waits for engine's update (async) state
    print("There") --Prints "There"
end)
```