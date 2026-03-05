# Differences between `struct` and `class`


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


For more details on `struct` in C and C++, see [struct那些事](../struct).


In summary, a `struct` is generally viewed as an **implementation of a data structure**, while a `class` is more naturally regarded as an **implementation of an object**.


### Key differences


The most fundamental difference is the **default access level**:

- For `struct`, the default access control for members and the default inheritance access are **`public`**.  
- For `class`, the default access control for members and the default inheritance access are **`private`**.

As a data‑structure implementation, `struct` defaults to `public` data access, making it suitable for simple groupings of data.  
As an object‑oriented implementation, `class` defaults to `private` member access, emphasizing encapsulation and behavior (methods) over raw data exposure.