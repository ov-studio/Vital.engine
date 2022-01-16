---
description: Awaits thread until the engine renders.
---

# waitEngineRender

<mark style="color:red;">**`[bool status] waitEngineRender()`**</mark>

### ━ Usage

```lua
vEngine.thread.create(function() --Creates a new thread
    print("Hello") --Prints "Hello"
    vEngine.thread.waitEngineRender() --Waits for engine's render state
    print("There") --Prints "There"
end)
```