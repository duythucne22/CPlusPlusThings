## About the Author


WeChat official account:


![](../img/wechat.jpg)


## 1. Meaning of const


A *const type* (constant type) is a type declared with the **const** type specifier. The value of a const‑type variable or object cannot be modified after it is initialized.


## 2. Role of const


+ Can define constants


```cpp
const int a = 100;
```


+ Type checking


    + Difference between `const` constants and `#define` macro constants:
    > <strong><s>const constants have a type, so the compiler can perform safety checks; `#define` macros have no data type and are just simple string replacements, so they cannot be checked for safety.</s></strong>  
    Many thanks to the two contributors who pointed out the issue here; see: [issue](https://github.com/Light-City/CPlusPlusThings/issues/5)


    + `const` constants can support all types.
    + In other cases it is just a `const`‑qualified variable; do not confuse it with compile‑time constants.


+ Prevent modification, adds protection, and improves program robustness


```cpp
void f(const int i) {
    i++; // error!
}
```


+ Can save space and avoid unnecessary memory allocations


    + From the assembly perspective, `const`‑defined constants only give the corresponding memory address, rather than immediate constants like `#define`.
    + `const`‑defined constants have only one copy in memory during program execution, whereas `#define`‑defined constants may have multiple copies.


## 3. const objects are file‑local by default


<p><font style="color:red">Note: non‑`const` variables are `extern` by default. To allow a `const` variable to be accessed from other files, you must explicitly declare it as `extern` in that file.</font></p>


> Accessing non‑`const` variables across files


```cpp
// file1.cpp
int ext;
// file2.cpp
#include <iostream>

extern int ext;
int main() {
    std::cout << (ext + 10) << std::endl;
}
```


> Accessing `const` constants across files


```cpp
// extern_file1.cpp
extern const int ext = 12;
// extern_file2.cpp
#include <iostream>
extern const int ext;
int main() {
    std::cout << ext << std::endl;
}
```


> Summary:  
> Notice that non‑`const` variables do not need an explicit `extern` declaration!  
> In contrast, `const` constants must be explicitly declared as `extern` and must be initialized because a constant cannot be modified after definition, so it must be initialized at definition.</p>


## 4. Defining constants


```cpp
const int b = 10;
b = 0; // error: assignment of read‑only variable ‘b’
const std::string s = "helloworld";
const int i, j = 0; // error: uninitialized const ‘i’
```


There are two errors above:
+ `b` is a constant and cannot be changed!
+ `i` is a constant and must be initialized! (Because a constant cannot be modified after definition, it must be initialized at declaration.)


## 5. Pointers and const


There are four common patterns involving `const` and pointers:


```cpp
const char *a;        // pointer to const object, or pointer to const char.
char const *a;        // same as above.
char * const a;       // const pointer to non‑const char, a “const pointer”.
const char * const a; // const pointer to const char.
```


> **Summary:**  
> If `const` is to the left of `*`, it modifies the pointed‑to value (what the pointer points to is constant).  
> If `const` is to the right of `*`, it modifies the pointer itself (the pointer is constant).  


**Another way to read it:**  
Read from right to left in English, treating `to` as the separator.  
Before `to` describes the pointer; after `to` describes the target.  

```cpp
const char *p;        // p is a pointer to const char
char const *p;        // same as above
char * const p;       // p is a const pointer to char
const char * const p; // p is a const pointer to const char
```

When a pointer itself is `const`, it cannot change the address it points to.  
If the target type is `char`, the pointed‑to content can be modified via the pointer, e.g., `*p = 'y';`.  
If the target type is `const char`, the content cannot be modified via the pointer.  


Concrete usage examples follow:


### (1) Pointer to const (pointer to constant)


```cpp
const int *ptr;
*ptr = 10; // error
```


`ptr` is a pointer to a `const int` object. The `const` applies to the `int` type, i.e., the type of the object `ptr` points to, not to `ptr` itself. So `ptr` may be left uninitialized, but you cannot modify the pointed‑to object through `ptr`.


In addition, you cannot use a `void*` pointer to store the address of a `const` object; you must use a `const void*` pointer to store the address of a `const` object.  


```cpp
const int p = 10;
const void * vp = &p;
void * vp = &p; // error
```


An important point: **you may assign the address of a non‑`const` object to a pointer to `const`**.  


Assigning a non‑`const` object’s address to a pointer to `const`:

```cpp
const int *ptr;
int val = 3;
ptr = &val; // ok
```


You cannot use `ptr` to modify the value of `val`, even though `val` is non‑`const`!  

You cannot use a pointer to `const` to modify the underlying object, yet if that pointer points to a non‑`const` object, you can modify it in other ways. You may modify the value that a `const` pointer points to, but not via that `const` pointer itself. For example:

```cpp
int *ptr1 = &val;
*ptr1 = 4;
std::cout << *ptr << std::endl;
```


> Summary:  
> 1. For a pointer to const, you cannot modify the object’s value through the pointer.  
> 2. You cannot use a `void*` pointer to store the address of a `const` object; you must use `const void*`.  
> 3. You may assign a non‑`const` object’s address to a pointer to `const`. If you need to modify the object’s value, do it via another non‑`const` pointer; you cannot modify it directly through the current `const` pointer.


### (2) Constant pointer (const pointer)


A `const` pointer must be initialized, and it may change the value it points to, but its target address cannot change.  


```cpp
#include <iostream>
using namespace std;

int main() {
    int num = 0, num1 = 1;
    int * const ptr = &num; // const pointer must be initialized; its target cannot change
    ptr = &num1; // error! const pointer cannot change its target
    cout << *ptr << endl;
}
```


This code produces a compilation error: a const pointer cannot change its target.  


```cpp
#include <iostream>
using namespace std;
int main() {
    int num = 0, num1 = 1;
    int * const ptr = &num; // must be initialized; target cannot change
    *ptr = 1;
    cout << *ptr << endl;
}
```


This code works fine and prints `1`.  


Finally, when you try to assign the address of a `const` constant to such a `ptr`, because `ptr` points to a non‑`const` variable, the compiler will complain with an error like `const int* -> int*`:

```cpp
#include <iostream>
using namespace std;
int main() {
    const int num = 0;
    int * const ptr = &num; // error! const int* -> int*
    cout << *ptr << endl;
}
```


The above would be fine if you wrote `const int* ptr` or `const int* const ptr` instead.


### (3) Const pointer to const (const pointer to const object)


Once you understand the first two cases, this one is easier to follow:  


```cpp
const int p = 3;
const int * const ptr = &p; 
```


`ptr` is a const pointer pointing to a const `int` object.


## 6. Using const in functions


> `const` applied to function return values


This is conceptually similar to using `const` with ordinary variables and pointers:  


### (1) `const int`


```cpp
const int func1();
```


This is essentially meaningless, since the return value just gets assigned to another variable anyway.  


### (2) `const int*`


```cpp
const int* func2();
```


The content pointed to by the returned pointer cannot be changed.  


### (3) `int *const`


```cpp
int *const func2();
```


The pointer itself is constant (cannot be changed).  


> `const` applied to function parameters


### (1) Parameter and pointer itself are const inside the function body — typically meaningless


```cpp
void func(const int var);        // the parameter itself is const inside the function
void func(int *const var);       // the pointer itself is const inside the function
```


This notation indicates that the parameter cannot be modified inside the function, but it is not useful: `var` is just a parameter, and parameters are local to the function anyway. The same applies when the parameter is a pointer.  


For input parameters passed *by value*, the function automatically creates a temporary copy. Since the input parameter does not need protection, adding `const` to such value‑passed parameters is unnecessary.  


### (2) Pointer‑type parameter: the *pointed‑to* content is const


```cpp
void StringCopy(char *dst, const char *src);
```


Here, `src` is an input parameter and `dst` is an output parameter. By marking `src` as `const`, any attempt inside the function body to modify `src`’s content will be flagged by the compiler. This is one of the main benefits of using `const` here.  


### (3) Parameters as references — to improve efficiency and prevent modification


```cpp
void func(const A &a)
```


For non‑internal data types, a declaration like `void func(A a)` is inherently inefficient, because the function body will create a temporary `A` object to copy the argument, and construction, copying, and destruction of that object all take time.  


To improve efficiency, the function can be changed to `void func(A &a)`, since *reference* passing merely uses an alias for the argument without creating a temporary object.  


> However, `void func(A &a)` has a drawback:  
> *Reference* passing could allow modification of `a`, which you may not want.  
> The solution is simple: add `const`, turning the function into `void func(const A &a)`.  


By the same reasoning, should `void func(int x)` become `void func(const int &x)` to improve efficiency?  
No. Internal types have no construction/destruction overhead, and copying them is fast; “value passing” and “reference passing” are almost equivalent in performance.  

> Summary:  
> 1. For non‑internal data‑type input parameters, change “value passing” to “const reference passing” to improve efficiency, e.g., turn `void func(A a)` into `void func(const A &a)`.  
> 2. For internal data‑type input parameters, do *not* change “value passing” to “const reference passing.” Doing so neither improves efficiency nor clarifies the code. For example, `void func(int x)` should not be rewritten as `void func(const int &x)`.


These points address two common interview questions:  

+ If a function takes a pointer, when (and where) should you add `const`, and what is the difference between putting `const` at different positions in the pointer type?  
+ If your function takes a complex‑type object, what is the difference between passing by value or by reference, and when should you mark a reference parameter as `const`?  


## 7. Using const in classes


In a class, any function that does not modify data members should be declared `const`. If, while writing a `const` member function, you accidentally modify a data member or call a non‑`const` member function, the compiler will report an error, which improves program robustness.  


Member functions declared with `const` are called **const member functions**. Only const member functions are allowed to operate on const objects or const data; non‑`const` member functions cannot be used to operate on const objects.  


`const` member variables inside a class must be initialized via the initialization list, as shown below:  

```cpp
class Apple {
private:
    int people;
public:
    Apple(int i); 
    const int apple_number;
};

Apple::Apple(int i) : apple_number(i) {}
```


A `const` object can call only `const` member functions, whereas a non‑`const` object can call any member function, including `const` ones.  


For example:  


```cpp
// apple.cpp
class Apple {
private:
    int people;
public:
    Apple(int i); 
    const int apple_number;
    void take(int num) const;
    int add();
    int add(int num) const;
    int getCount() const;
};

// apple.cpp
Apple::Apple(int i) : apple_number(i) {}

int Apple::add(int num) {
    take(num);
    return 0;
}

int Apple::add(int num) const {
    take(num);
    return 0;
}

void Apple::take(int num) const {
    std::cout << "take func " << num << std::endl;
}

int Apple::getCount() const {
    take(1);
    // add(); // error
    return apple_number;
}

int main() {
    Apple a(2);
    std::cout << a.getCount() << std::endl;
    a.add(10);

    const Apple b(3);
    b.add(100);
    return 0;
}
// main.cpp
```

> Compile: `bazel run basic_content/const/class_const/first_example:main`  


At this point the compiler reports an error: in `getCount()`, a non‑`const` `add()` is called, which is disallowed inside a `const` member function. This means a `const` member function can call only other `const` member functions.  


When you change the call to:  

```cpp
const Apple b(3);
b.add(); // error
```  

this demonstrates that a `const` object can only call `const` member functions.  


Besides using the initialization list, `const` member variables can also be initialized in another way:  


First, combine `const` with `static`:  

```cpp
static const int apple_number;
```  

Second, define and initialize it outside the class:  

```cpp
const int Apple::apple_number = 10;
```  

If you compile with C++11, you can also initialize right at the declaration:  

```cpp
static const int apple_number = 10;
// or
const int apple_number = 10;
```  

Both forms are supported in C++11.  

Add `-std=c++11` when compiling.  


This leads us to `static`. Here is a brief note:  

In C++, `static` class members cannot be defined inside the class body; they can only be declared there. The definition must appear outside the class definition, typically in the implementation file.  

Inside the class:  

```cpp
static int ap;
```  

In the implementation file:  

```cpp
int Apple::ap = 666;
```  

Even in C++11, the above pattern is required for `static` class members; you still cannot define and initialize them directly inside the class body in this context.