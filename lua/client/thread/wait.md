---
description: Awaits thread for 'n' duration before running again.
---

# wait

{% hint style="danger" %}
**API available only within a valid thread.**
{% endhint %}

### ━ Syntax

<mark style="color:red;">**`[bool status] wait(int seconds)`**</mark>

```lua
vEngine.thread.create(function() --Creates a new thread
    print("Hello") --Prints "Hello"
    vEngine.thread.wait(5) --Waits 5 second before printing "There"
    print("There") --Prints "There"
end)
```
