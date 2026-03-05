# Stories About `virtual`


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 1. Virtual functions and runtime polymorphism


Corresponding code: [emp.cpp](./set1/emp.cpp)


**The version of a virtual function that is called depends on the actual type of the object pointed to or referenced, not on the type of the pointer or reference itself.**


## 2. vptr and vtable


See [vptr_vtable那些事](../vptr_vtable).


## 3. Virtual functions with default arguments


Corresponding code: [default_arg.cpp](./set2/default_arg.cpp)


**Default arguments are statically bound, while virtual functions are dynamically bound. The choice of default arguments depends on the type of the pointer or reference, not on the type of the underlying object.**


## 4. Can / cannot be virtual


### (1) Can a static function be declared as virtual?

**Static member functions cannot be declared as virtual, and also cannot be modified by `const` or `volatile`.**  

There are two main reasons:

- A `static` member function does not belong to any object or class instance, so it is meaningless to try to make it virtual.
- Virtual functions rely on `vptr` and `vtable` for dispatch. The `vptr` is a pointer that is set up in the constructor and accessed via `this`. Static functions have no `this` pointer, so they cannot access or use `vptr`.

Code to study: [static_error.cpp](./set3/static_error.cpp)


### (2) Can a constructor be virtual?

**Constructors cannot be declared as virtual.**  
Besides `inline` and `explicit`, constructors are not allowed to use any other specifiers.

Why can’t a constructor be virtual?

- Although the `vtable` is generated at compile time, the `vptr` (pointer to `vtable`) is created at runtime when an object is instantiated.  
- If a class has virtual functions, the compiler injects code into the constructor to initialize `vptr`.  
- If the constructor itself were virtual, it would need `vptr` to access the `vtable`, but `vptr` does not yet exist, creating a circular dependency.

We use virtual functions when we have incomplete information at runtime and want polymorphic behavior. However, a constructor is used to initialize an object whose type is already clearly known, so there is no need to make it virtual.

Code to study:

- [copy_consrtuct.cpp](./set3/copy_consrtuct.cpp)
- [vir_con.cpp](./set3/vir_con.cpp)


### (3) Can a destructor be virtual?

**Destructors can be declared as virtual.**  
If you ever need to delete a base‑class pointer that points to a derived‑class object, the destructor should be declared virtual. In fact, **whenever a class may be inherited by others, it should declare a virtual destructor (even if that destructor does nothing)**.

Code to study:

- [full_virde.cpp](./set3/full_virde.cpp)
- [vir_de.cpp](./set3/vir_de.cpp)


### (4) Can a virtual function be private?

- When a base‑class pointer points to a derived‑class object, it still calls the derived‑class’s override of that function (through virtual dispatch).  
- The `main` function (or the caller) must be declared as a friend of the `Base` class, or else the code will fail to compile because the derived‑class pointer cannot access the private virtual function.  
- Alternatively, if the base‑class function is declared `public` and the derived‑class function is `private`, the problem goes away and the virtual call works normally.

Code to study:

- [virtual_function.cpp](./set3/virtual_function.cpp)
- [virtual_function1.cpp](./set3/virtual_function1.cpp)


### (5) Can a virtual function be inline?

**Ordinary (non‑`virtual`) class member functions can be inlined by the compiler, but virtual functions called via pointers or references cannot.**

- Virtual functions **can** be declared `inline`, but they **cannot be inlined** when they are used in a polymorphic context (via base‑class pointers or references).  
- Inlining is a compile‑time hint, whereas virtual dispatch is resolved at runtime. The compiler does not know at compile time which concrete function will be called, so it cannot inline such calls.  
- `inline virtual` can only be inlined when the compiler knows the exact class of the object (e.g., `Base::who()` on a concrete `Base` object), which happens only when the object is used directly, not via a pointer or reference.

Code to study:

- [virtual_inline.cpp](./set3/virtual_inline.cpp)
- [inline_virtual.cpp](./set3/inline_virtual.cpp)


## 5. RTTI and `dynamic_cast`


RTTI (Run‑Time Type Identification) allows a program to use a base‑class pointer or reference to examine the actual derived‑class type of the object pointed to or referenced.

In object‑oriented programming, we sometimes need to query at runtime whether an object can be treated as a certain polymorphic type. Similar to Java’s `instanceof` or C#’s `is`/`as` operators, C++ provides `dynamic_cast` for dynamic type checking and type‑safe downcasts. Compared with C‑style casts and `reinterpret_cast`, `dynamic_cast` performs runtime type checking and is therefore recommended for safe conversions between polymorphic types.

Code to study:

- [rtti.cpp](./set4/rtti.cpp)
- [warn_rtti.cpp](./set4/warn_rtti.cpp)


## 6. Pure virtual functions and abstract classes


See [pure‑virtual functions and abstract classes](../abstract).