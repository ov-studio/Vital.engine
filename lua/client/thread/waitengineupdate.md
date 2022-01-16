---
description: Awaits thread until the engine updates.
---

# waitEngineUpdate

{% hint style="danger" %}
**API available only within a valid thread.**
{% endhint %}

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
