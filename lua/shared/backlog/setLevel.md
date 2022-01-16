---
description: Sets backlog level.
---

# setLevel

{% hint style="danger" %}
**API available only on Client Side.**
{% endhint %}

### ━ Syntax

<mark style="color:red;">**`[bool status] setLevel(int level)`**</mark>

### ━ Levels

* **0 - None**
* **1 - Default**
* **2 - Warning**
* **3 - Error**

### ━ Usage

```lua
local result = vEngine.backlog.setLevel(1) --Set our backlog level to default mode
print(result) --Prints result
```