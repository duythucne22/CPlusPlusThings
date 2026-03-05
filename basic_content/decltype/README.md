# Stories About `decltype`


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 1. Basic usage


The syntax of `decltype` is:

```text
decltype(expression)
```

The parentheses are mandatory. The purpose of `decltype` is to **query the type of an expression**, so the above statement returns the type of `expression`. Note that `decltype` only **queries** the type and does **not evaluate** the expression.


### 1.1 Deduce the type of an expression


```cpp
int i = 4;
decltype(i) a; // deduced as int; a has type int
```


### 1.2 Working with `using` / `typedef` for type definitions


```cpp
using size_t = decltype(sizeof(0));                                   // sizeof(…) returns size_t
using ptrdiff_t = decltype((int*)0 - (int*)0);
using nullptr_t = decltype(nullptr);

std::vector<int> vec;
typedef decltype(vec.begin()) vectype;

for (vectype i = vec.begin(); i != vec.end(); ++i) {
    // ...
}
```

Just like `auto`, this improves code readability by letting the compiler compute the type from an expression.


### 1.3 Reuse of anonymous types


In C++ we sometimes encounter **anonymous types**, such as:

```cpp
struct
{
    int d;
    double b;
} anon_s;
```

With `decltype`, we can reuse this anonymous structure:

```cpp
decltype(anon_s) as;  // declares another variable of the same anonymous struct type
```


### 1.4 Generic programming: combining `auto` and `decltype` for return‑type deduction


This is probably the most important use of `decltype`:

```cpp
template <typename T>
auto multiply(T x, T y) -> decltype(x * y)
{
    return x * y;
}
```

The `-> decltype(x*y)` part lets the function return the type of `x * y` without the caller having to specify it manually.

Full code: [decltype.cpp](decltype.cpp)


## 2. Deduction rules


For `decltype(e)`, the result depends on the following rules:

1. If `e` is an **unparenthesized name (identifier) expression** or a **class member access** expression, then `decltype(e)` is the type of the entity that `e` names.  
   If `e` names an **overloaded function**, the program is ill‑formed (compile error).

2. Otherwise, suppose `e` has type `T`:  
   - If `e` is an **xvalue** (an expiring value, such as a function returning `T&&`), then `decltype(e)` is `T&&`.  
   - If `e` is an **lvalue**, then `decltype(e)` is `T&`.  
   - Otherwise, `decltype(e)` is `T` (the plain type of `e`).

An **identifier** here means a programmer‑defined name (excluding keywords and literals); a single identifier by itself forms an **identifier expression**. For example:

```cpp
int arr; [stackoverflow](https://stackoverflow.com/questions/9259451/size-of-class-c/9259489)
```

Here, `arr` is an identifier expression; `arr [dominikgrabiec](https://www.dominikgrabiec.com/posts/2025/02/01/how_to_layout_data_in_classes.html) + 0` is not.

Examples:

```cpp
int i = 4;
int arr = {0}; [cnblogs](https://www.cnblogs.com/scw2901/p/4452620.html)
int* ptr = arr;
struct S { double d; } s;
void Overloaded(int);
void Overloaded(char);        // overloaded function
int&& RvalRef();
const bool Func(int);

// Rule 1: identifier / member access -> plain type
decltype(arr) var1;            // int[]: array of int  (identifier expression)
decltype(ptr) var2;            // int*                (identifier expression)
decltype(s.d) var3;            // double              (member access expression)
// decltype(Overloaded) var4;  // error: overloaded function name

// Rule 2: xvalue -> T&&
decltype(RvalRef()) var5 = 1;  // int&&

// Rule 3: lvalue -> T&
decltype((i)) var6 = i;        // int&; (i) is an lvalue expression
decltype(true ? i : i) var7 = i; // int&; the conditional yields an lvalue
decltype(++i) var8 = i;        // int&; ++i returns an lvalue
decltype(arr) var9 = i;     // int&; subscript returns an lvalue [cnblogs](https://www.cnblogs.com/scw2901/p/4452620.html)
decltype(*ptr) var10 = i;      // int&; dereference returns an lvalue
decltype("hello") var11 = "hello"; // const char(&): character string literal is a const lvalue [dominikgrabiec](https://www.dominikgrabiec.com/posts/2025/02/01/how_to_layout_data_in_classes.html)

// Rule 4: otherwise, deduce as plain T
decltype(1) var12;             // int (prvalue) -> int
decltype(Func(1)) var13 = true; // const bool
decltype(i++) var14 = i;       // int; i++ returns int as prvalue
```

For further reading, see:  
https://www.cnblogs.com/QG-whz/p/4952980.html