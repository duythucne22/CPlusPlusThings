# Implementing C++‑style Object‑Orientation in C


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 1. C++ implementation example


Polymorphism in C++ is implemented via a **virtual‑function table (vtable)**. By the **assignment‑compatibility rule**, a pointer or reference to a base class can point to or bind to a derived‑class object.

If a base‑class pointer or reference calls a virtual function of the base class, the program looks up that function’s address in the base class’s own vtable. If the base‑class pointer or reference actually points to a derived‑class object, and the derived class has overridden the virtual function, the call will resolve to the overridden version in the derived class.

Example code: [c++_examp.cpp](./c++_examp.cpp)


## 2. Object‑oriented simulation in C


### Encapsulation


C does not have a `class` concept, but it does have `struct`. We can use `struct` to simulate classes.

Member data and “methods” can be encapsulated by adding **function pointers** to the `struct`:

```c
struct Base {
    int data;
    void (*func)(struct Base *this);
};
```

The `this`‑like pointer is passed explicitly to simulate C++‑style member‑function access.


### Inheritance


In C, inheritance is simulated by **embedding a parent structure as the first member of a child structure**. For example:

```c
struct Derived {
    struct Base base;   // must be first
    int extra_field;
};
```

Because `Base` is the first member, a `Derived*` pointer can be safely cast to `Base*`, mimicking C++‑style inheritance and enabling code reuse.


### Polymorphism


In C, there is no built‑in virtual dispatch, so polymorphism is simulated by **function‑pointer tables**.

Each “class” (base and derived) has a structure of function pointers that correspond to the same set of methods, but point to different implementations:

```c
struct BaseVtable {
    void (*draw)(struct Base *this);
};

struct Base {
    struct BaseVtable *vtable;
    int x, y;
};

struct Derived {
    struct Base base;
    int color;
};
```

By keeping the **layout and order** of these function‑pointer tables aligned, a base‑class pointer pointing to a derived‑class object can call the correct “overridden” function. If the vtable layouts are misaligned, the program will typically crash at runtime.

However, this simulation has a drawback: each “vtable” is just a block of memory containing function pointers, and not automatically managed like C++’s language‑supplied vtables. If many virtual methods are simulated, maintenance becomes more complex.

To emulate polymorphism correctly, the function‑pointer variables in the parent and child must be **bit‑wise compatible and layout‑aligned**; otherwise, when a base‑class pointer points to a derived‑class object, the program may behave incorrectly or crash.

Example code: [c_examp.c](./c_examp.c)