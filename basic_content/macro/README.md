# Stories About Macros


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 1. Macros with special operators


There are several special operators inside macros: `#`, `##`, and `\`.


### 1.1 Stringization operator (`#`)


**When you put a `#` before a macro parameter, the preprocessor converts that parameter into a string literal.** In other words, `#` means “turn the following argument into a string”, and can only be used in parameterized macro definitions and must appear immediately before a parameter name in the macro body.

Example:

```cpp
#define exp(s)  printf("test s is:%s\n",s)
#define exp1(s) printf("test s is:%s\n",#s)
#define exp2(s) #s

int main() {
    exp("hello");
    exp1(hello);

    std::string str = exp2(   bac );
    std::cout << str << " " << str.size() << std::endl;

    std::string str1 = exp2( asda  bac );
    std::cout << str1 << " " << str1.size() << std::endl;
    return 0;
}
```

The code above shows basic usage and how whitespace is handled:

- **Leading and trailing whitespace around the argument is ignored.**

```cpp
std::string str = exp2(   bac );
std::cout << str << " " << str.size() << std::endl;
```

Output:
```
bac 3
```

- **When there are multiple tokens separated by spaces in the argument, the preprocessor concatenates them into one string, joined by a single space and ignoring extra spaces.**

```cpp
std::string str1 = exp2( asda  bac );
std::cout << str1 << " " << str1.size() << std::endl;
```

Output:
```
asda bac 8
```


### 1.2 Token‑pasting (concatenation) operator (`##`)


**`##` is a token‑pasting operator: it first “splits” identifiers, then forces them to be concatenated into a single token.** It is often used to combine macro parameters into a concrete name.

Important points:

- **Spaces around `##` are optional.**  
- **The resulting token must be a valid existing identifier or a known macro.**  
- **If the operand after `##` is itself a macro, `##` prevents it from being expanded.**

Example:

```cpp
#define expA(s)  printf("After adding prefix: %s\n",gc_##s)   // gc_hello must exist
#define expB(s)  printf("After adding prefix: %s\n",gc_  ##  s)   // same as above, with spaces
#define gc_hello1 "I am gc_hello1"

int main() {
    const char *gc_hello = "I am gc_hello";
    expA(hello);   // expands to gc_hello
    expB(hello1);  // expands to gc_hello1
}
```


### 1.3 Line‑continuation operator (`\`)


**When a macro definition cannot fit on a single line, you can use `\` at the end of a line to indicate that the macro continues on the next line.**

Note: **Leave no space after `\`.**

Example:

```cpp
#define MAX(a,b) ((a)>(b) ? (a) \
   :(b))

int main() {
    int max_val = MAX(3,6);
    std::cout << max_val << std::endl;
}
```

Source file: [sig_examp.cpp](sig_examp.cpp)


## 2. Using `do{...}while(0)` in macros


### 2.1 Avoiding semantic misinterpretation


Consider:

```cpp
#define fun()  f1();f2();
if (a > 0)
    fun()
```

After expansion, it becomes:

```cpp
if (a > 0)
    f1();
    f2();
```

This is not the intended logic; `f2` executes unconditionally. A common fix is to wrap the macro body in `{}`:

```cpp
#define fun()  { f1(); f2(); }
if (a > 0)
    fun();
```

Expanded:

```cpp
if (a > 0) {
    f1();
    f2();
};
```

However, the trailing semicolon leads to slightly awkward syntax, even though it still compiles.


### 2.2 Replacing `goto`


Sometimes functions must do cleanup before returning, such as freeing memory allocated with `malloc`:

```cpp
int f() {
    int *p = (int *)malloc(sizeof(int));
    *p = 10;
    std::cout << *p << std::endl;

#ifndef DEBUG
    int error = 1;
#endif

    if (error)
        goto END;

    // do something
END:
    std::cout << "free" << std::endl;
    free(p);
    return 0;
}
```

Because `goto` can harm readability and structure, people often prefer `do{...}while(0)`:

```cpp
int ff() {
    int *p = (int *)malloc(sizeof(int));
    *p = 10;
    std::cout << *p << std::endl;

    do {
#ifndef DEBUG
        int error = 1;
#endif
        if (error)
            break;
        // do something
    } while (0);

    std::cout << "free" << std::endl;
    free(p);
    return 0;
}
```

The main body is inside `do{...}while(0)`; `break` replaces `goto`, and cleanup happens after the loop. The code is more readable and maintainable.


### 2.3 Avoiding empty‑macro warnings


In the kernel and large projects, empty macros can trigger compiler warnings. Using `do{...}while(0)` avoids this:

```cpp
#define EMPTYMACRO  do{}while(0)
```


### 2.4 Defining a single block for complex logic


If a function is complex and you don’t want to split it into smaller functions, you can use `do{...}while(0)` to contain a local block with its own variables:

```cpp
int fc()
{
    int k1 = 10;
    std::cout << k1 << std::endl;

    do {
        int k1 = 100;
        std::cout << k1 << std::endl;
    } while (0);

    std::cout << k1 << std::endl;
}
```

Source file: [do_while.cpp](do_while.cpp)

Reference article:  
<https://www.cnblogs.com/lizhenghn/p/3674430.html>