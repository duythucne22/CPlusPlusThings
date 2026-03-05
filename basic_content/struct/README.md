# One Article to Understand `struct` in C and C++


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 1. `struct` in C


In C, `struct` is merely a **composite data type** used to group variables together. Key characteristics:

- A C `struct` can contain **only data members**, not functions.
- C‑style `struct` declarations cannot use C++ access specifiers such as `public`, `protected`, or `private` (these are not allowed).
- In C, when you declare a variable of a `struct` type, you must write `struct` explicitly, for example: `struct Base base;`.
- C `struct` types **cannot inherit** from other types (inheritance is not a concept in C).
- A `struct` name can be the same as a function name; both can coexist and be used normally. For example, you can define a function `void Base() {}` even if there is a `struct Base`.


Complete example:

```c
#include <stdio.h>

struct Base {            // public
    int v1;
//    public:      // error
        int v2;
    //private:
        int v3;
    //void print(){       // C cannot contain functions inside a struct
    //    printf("%s\n","hello world");
    //};    // error!
};

void Base(){
    printf("%s\n","I am Base func");
}
//struct Base base1;  // ok
//Base base2; // error

int main() {
    struct Base base;
    base.v1 = 1;
    //base.print();
    printf("%d\n",base.v1);
    Base();
    return 0;
}
```

Output:

```
1
I am Base func
```

Full code: [struct_func.c](./struct_func.c)


## 2. `struct` in C++


Compared with C, C++ `struct` is much more powerful:

- A C++ `struct` can contain both **data members and functions**.
- C++ `struct` can use access specifiers such as `public`, `protected`, and `private`.  
  (By default, all members of a `struct` are `public`.)
- In C++, you can declare a `struct` variable **without** writing the `struct` keyword, e.g., `Base base;`.
- C++ `struct` supports **inheritance**.
- If a `struct` name is the same as a function name, they can coexist, but when declaring a variable of that type you must use `struct` if the name is also used as a function.


Examples:

### Case 1: No `typedef` alias

Without an identically‑named function:

```cpp
struct Student {

};
//Student(){}   // function
struct Student s; // ok
Student s;       // ok
```

After adding a function with the same name:

```cpp
struct Student {

};
Student(){}
struct Student s; // ok
Student s;        // error: Student now refers to the function
```


### Case 2: Using `typedef` to alias the `struct`

```cpp
typedef struct Base1 {
    int v1;
    int v3;
public:        // explicitly declare public
    int v2;
    void print(){
        printf("%s\n","hello world");
    };
} B;

//void B() {}  // error! "B" is already an alias for struct Base1
```


### Basic C++ `struct` with functions

```cpp
#include <iostream>
#include <stdio.h>

struct Base {
    int v1;
//    private:   // error in C
        int v3;
public:        // explicitly declare public
    int v2;
    void print(){
        printf("%s\n","hello world");
    };
};

int main() {
    struct Base base1;  // ok
    Base base2;         // ok
    Base base;
    base.v1 = 1;
    base.v3 = 2;
    base.print();
    printf("%d\n",base.v1);
    printf("%d\n",base.v3);
    return 0;
}
```

Full code: [struct_func.cpp](struct_func.cpp)


### Inheritance example

```cpp
#include <iostream>
#include <stdio.h>

struct Base {
    int v1;
//    private:   // error in C
        int v3;
public:        // explicitly declare public
    int v2;
    virtual void print(){
        printf("%s\n","Base");
    };
};

struct Derived : Base {

public:
    int v2;
    void print(){
        printf("%s\n","Derived");
    };
};

int main() {
    Base *b = new Derived();
    b->print();
    return 0;
}
```

Full code: [ext_struct_func.cpp](./ext_struct_func.cpp)


### Name collision with function

```cpp
#include <iostream>
#include <stdio.h>

struct Base {
    int v1;
//    private:   // error in C
        int v3;
public:        // explicitly declare public
    int v2;
    void print(){
        printf("%s\n","hello world");
    };
};

typedef struct Base1 {
    int v1;
//    private:   // error in C
        int v3;
public:        // explicitly declare public
    int v2;
    void print(){
        printf("%s\n","hello world");
    };
} B;

void Base(){
    printf("%s\n","I am Base func");
}
//void B() {}  // error! "B" is already an alias for struct Base1

int main() {
    struct Base base;  // ok
    //Base base1;      // error, because "Base" is a function here
    base.v1 = 1;
    base.v3 = 2;
    base.print();
    printf("%d\n",base.v1);
    printf("%d\n",base.v3);
    Base();
    return 0;
}
```

Full code: [struct_func_func.cpp](./struct_func_func.cpp)


## 3. Summary


### Differences between `struct` in C and in C++


| C `struct`                                        | C++ `struct`                                                   |
|---------------------------------------------------|----------------------------------------------------------------|
| Cannot contain functions.                         | Can contain both data and functions.                          |
| Cannot use C++ access specifiers `public`, etc.   | Can use `public`, `protected`, `private`.                     |
| Must write `struct` to declare variables.         | Can declare variables without `struct`.                       |
| No inheritance.                                   | Supports inheritance.                                         |
| Can share names with functions normally.          | If a `struct` name collides with a function, variables must be declared with `struct`. |
