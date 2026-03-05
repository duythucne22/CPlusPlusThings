# Stories About `assert`


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)




## 1. First assertion example


An **assertion is a macro, not a function**.


The prototype of the `assert` macro is defined in `<assert.h>` (C) and `<cassert>` (C++). Its purpose is to terminate the program if the condition it checks evaluates to false.


You can turn off `assert` by defining the macro `NDEBUG`, **but this must be done before `#include <assert.h>` (or `<cassert>`) at the top of the source file**.

```c
void assert(int expression);
```


> Code example: [assert.c](./assert.c)

```c
#include <stdio.h>
#include <assert.h>

int main()
{
    int x = 7;

    /*  Some big code in between and, let's say, x
        is accidentally changed to 9  */
    x = 9;

    // Programmer assumes x is 7 for the rest of the code
    assert(x == 7);

    /* Rest of the code */

    return 0;
}
```

Output:

```text
assert: assert.c:13: main: Assertion 'x==7' failed.
```

As you can see, the error message shows the source file, line number, and the failed condition, making it very useful for debugging.


## 2. Assertions vs normal error handling


+ **Assertions are mainly used to check logically impossible situations.**

> For example, they can be used to verify the expected state of the program at the beginning of a function, or the expected state at the end of a function. Unlike normal error‑handling mechanisms, assertions can be (and often are) disabled at runtime.

+ To **disable assertions globally**, add the following line at the top of the code:

```cpp
#define NDEBUG      // With this line, assert is disabled
```

> Sample code: [ignore_assert.c](./ignore_assert.c)