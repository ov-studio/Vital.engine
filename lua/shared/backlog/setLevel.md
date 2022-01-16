---
description: Sets backlog level.
---

# setLevel

{% hint style="danger" %}
**API available only on Client Side.**
{% endhint %}

### ━ Syntax

<mark style="color:red;">**`[bool state] setLevel(int level)`**</mark>

### ━ Levels

* **1 - None**
* **2 - Default**
* **3 - Warning**
* **4 - Error**

### ━ Usage

```lua
local state = vEngine.backlog.setLevel() --Retrieves our backlog's state
print(state) --Prints state
```