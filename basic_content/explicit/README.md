# Stories About the `explicit` (explicit) keyword


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


- When `explicit` is applied to a **constructor**, it prevents **implicit conversions** and **copy initialization**; the constructor can then be used only in **direct initialization** or with an explicit cast.  
- When `explicit` is applied to a **conversion function** (e.g., `operator bool`), it prevents **implicit conversions**, except in **context‑sensitive conversions** (such as conditions in `if`, `while`, loops, etc., where the compiler is allowed to convert to `bool` explicitly).

Sample code: [explicit.cpp](./explicit.cpp)

Reference links:  
> [https://stackoverflow.com/questions/4600295/what-is-the-meaning-of-operator-bool-const](https://stackoverflow.com/questions/4600295/what-is-the-meaning-of-operator-bool-const)