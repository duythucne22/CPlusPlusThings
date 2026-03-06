# Day 1 — Basics and Beyond (Learning Notes)

Personal notes while reading and running the examples under `basic_content/`.

## Quick commands

```bash
# Run an example
bazel run //basic_content/<dir>:<target>

# Build-only (useful when the lesson intentionally fails to compile)
bazel build //basic_content/<dir>:<target>
```

---

## 1) `const`

**Run**
```bash
bazel run //basic_content/const:const_num
bazel run //basic_content/const:const_function
```

**Key rules**
- A `const` variable must be initialized at declaration.
- A `const` value cannot be assigned to after initialization.
- `const` on a function parameter makes it read‑only inside that function.

**Code**
- `basic_content/const/const_num.cpp`
- `basic_content/const/const_function.cpp`

---

## 2) `static`

**Run**
```bash
bazel run //basic_content/static:static_demo
bazel run //basic_content/static:static_variable
bazel run //basic_content/static:static_funciton
bazel run //basic_content/static:nostatic_class
bazel run //basic_content/static:static_class
```

**What I learned**
- Function-local `static` variables are initialized once and **persist across calls**.
- `static` class data members are **shared across all instances** and must be **defined outside** the class.
- `static` member functions have no `this` and can be called as `ClassName::func()`.
- A local `static` object’s lifetime is extended to **program exit** (destructor runs after `main()` returns).

**Code**
- `basic_content/static/static_demo.cpp`
- `basic_content/static/static_variable.cpp`
- `basic_content/static/static_funciton.cpp`
- `basic_content/static/nostatic_class.cpp`
- `basic_content/static/static_class.cpp`

---

## 3) `this`

**Run**
```bash
bazel run //basic_content/this:person
```

**What `this` is**
- In any non‑static member function, `this` is an implicit pointer to the current object.
- `this->member` and `member` are equivalent (unless there’s a naming conflict).

**Method chaining pattern**
```cpp
Person& add_age(int a) {
  age += a;
  return *this;
}
```
This enables `p.add_age(1).add_age(2);`.

**Note**
- If you see a warning about assigning a string literal to `char*`, prefer `const char*` or `std::string`.

**Code**
- `basic_content/this/person.cpp`

---

## 4) `inline`

**Run**
```bash
bazel run //basic_content/inline:main
bazel run //basic_content/inline:inline_virtual
```

**Key rules**
- `inline` is a compiler hint (and also affects ODR/linkage for functions defined in headers).
- Putting a function definition in a header usually requires it to be `inline` (explicitly or implicitly).
- Functions defined inside a class definition are implicitly `inline`.

**`inline` vs `virtual`**
- Virtual dispatch is resolved at runtime, so calls through base pointers/references generally can’t be inlined.
- Compilers *may* devirtualize in some cases (e.g., they can prove the dynamic type), but don’t rely on it.

**Code**
- `basic_content/inline/inline.h`
- `basic_content/inline/inline.cpp`
- `basic_content/inline/inline_virtual.cpp`

---

## 5) `sizeof` (alignment + “empty class = 1”)

**Run**
```bash
bazel run //basic_content/sizeof:blackclass
bazel run //basic_content/sizeof:genA
bazel run //basic_content/sizeof:geninhe
```

**Key rules**
- `sizeof(empty_class)` is **not 0** (typically 1) so distinct objects have distinct addresses.
- Member functions do not contribute to object size; **only non‑static data members** do.
- Padding/alignment often makes `sizeof` larger than the sum of member sizes.
- Sizes are platform/ABI dependent (e.g., `sizeof(long)` differs between LLP64 and LP64).

**Code**
- `basic_content/sizeof/blackclass.cpp`
- `basic_content/sizeof/genA.cpp`
- `basic_content/sizeof/geninhe.cpp`

---

## 6) Function pointers

**Run**
```bash
bazel run //basic_content/func_pointer:func_pointer
```

**Key idea**
- Function pointers let you store a function (by address) and call it later (callbacks, jump tables, etc.).

**Code**
- `basic_content/func_pointer/func_pointer.cpp`

---

## 7) Pure virtual functions & abstract classes

**Run**
```bash
bazel run  //basic_content/abstract:derived_full
bazel run  //basic_content/abstract:abstract
# some targets intentionally fail to build:
bazel build //basic_content/abstract:pure_virtual
```

**Core facts**
- A class with at least one `= 0` function is abstract (cannot instantiate).
- You can hold abstract types via pointers/references to concrete derived objects.
- If a derived class doesn’t override all pure virtuals, it remains abstract.
- Abstract classes can have constructors (called by derived constructors).
- For polymorphic bases, use a **virtual destructor** if you ever delete via `Base*`.

**Code**
- `basic_content/abstract/abstract.cpp`
- `basic_content/abstract/derived_full.cpp`
- `basic_content/abstract/pure_virtual.cpp`

---

## 8) `vptr` and `vtable` (implementation detail)

**Run**
```bash
bazel run //basic_content/vptr_vtable:vptr1
```

**What I learned**
- Many C++ ABIs implement virtual dispatch with a hidden per‑object pointer (often called `vptr`) that points to a per‑class table of function pointers (`vtable`).
- This is how `Base* p = new Derived; p->virtual_func();` typically finds `Derived::virtual_func()` at runtime.

**Important note**
- “vptr/vtable layout” is not specified by the C++ standard; it’s a common implementation strategy.

**Code**
- `basic_content/vptr_vtable/vptr1.cpp`

---

## 9) `virtual` — common traps

**Run**
```bash
bazel run  //basic_content/virtual/set1:emp
bazel run  //basic_content/virtual/set2:default_arg
bazel run  //basic_content/virtual/set3:vir_de
bazel build //basic_content/virtual/set3:static_error
```

**Key rules**
- Virtual calls dispatch based on the *dynamic* type of the object.
- Default arguments are bound *statically* (based on the static type, e.g. `Base*`), even for virtual functions.
- If you delete through a base pointer, the base should have `virtual ~Base()`.
- `static` and `virtual` don’t mix: static member functions have no `this`, so virtual dispatch can’t work.

**Extra reading**
- `basic_content/virtual/README.md`
- `basic_content/virtual/set3/virtual_function.cpp` (private virtual + `friend main`)
- `basic_content/virtual/set4/rtti.cpp` (RTTI + `dynamic_cast`)

---

## 10) `volatile` (and what it is *not*)

**Run**
```bash
bazel run //basic_content/volatile:volatile
bazel run //basic_content/volatile:noopt_vola
```

**What `volatile` means**
- It prevents the compiler from optimizing away loads/stores to that object (always “touch memory”).

**What it does *not* mean**
- It does not make code thread-safe; for concurrency, prefer `std::atomic` / proper synchronization.

**Caution**
- Examples that “cast away const and write” are often **undefined behavior** in standard C++ (use them only as demonstrations of optimization effects, not as a technique).

**Code**
- `basic_content/volatile/volatile.cpp`
- `basic_content/volatile/noopt_vola.cpp`

---

## 11) `assert`

**Run**
```bash
bazel run //basic_content/assert:assert
bazel run //basic_content/assert:ignore_assert
```

**Key rules**
- `assert(expr)` is for debug-time invariants: it aborts when `expr` is false.
- Defining `NDEBUG` before including `<assert.h>` disables asserts (they become no-ops).

**Code**
- `basic_content/assert/assert.c`
- `basic_content/assert/ignore_assert.c`

---

## 12) Bit fields

**Run**
```bash
bazel run //basic_content/bit:bit
```

**Key idea**
- Bit fields pack multiple logical fields into a word, but layout is implementation-defined (be careful for on-the-wire formats).

**Code**
- `basic_content/bit/bit.cpp`

---

## 13) `extern "C"` (C/C++ linkage)

**Run**
```bash
bazel run //basic_content/extern/extern_c:add
bazel run //basic_content/extern/extern_c++:add
```

**Key idea**
- C++ name-mangles symbols; `extern "C"` tells the C++ compiler to use C linkage (no mangling) for that declaration/definition boundary.

**Code**
- `basic_content/extern/extern_c/add.h`
- `basic_content/extern/extern_c++/add.h`

---

## 14) `struct` (C vs C++)

**Run**
```bash
bazel run //basic_content/struct:struct_func
bazel run //basic_content/struct:struct_func_cpp
bazel run //basic_content/struct:struct_func_func
```

**Key points**
- In C++, `struct` and `class` are almost the same; the default access differs:
  - `struct` members are `public` by default
  - `class` members are `private` by default
- C++ lets you omit `struct` when declaring variables of a struct type (`Base b;`).

**Code**
- `basic_content/struct/struct_func.cpp`
- `basic_content/struct/struct_func_func.cpp`

---

## 15) `c_poly` (C-style “polymorphism”)

**Run**
```bash
bazel run //basic_content/c_poly:c_examp
bazel run //basic_content/c_poly:cpp_examp
```

**Key idea**
- In C, a common pattern is “polymorphism via struct + function pointers”.
- C++ `virtual` automates a similar mechanism (plus safety/typing features).

---

## 16) `explicit`

**Run**
```bash
bazel run //basic_content/explicit:explicit
```

**Key rule**
- Mark single-argument constructors `explicit` to block unintended implicit conversions.

**Code**
- `basic_content/explicit/explicit.cpp`

---

## 17) `friend`

**Run**
```bash
bazel run //basic_content/friend:friend_func
bazel run //basic_content/friend:friend_class
```

**Key idea**
- `friend` bypasses access control (`private`/`protected`) for specific functions/classes.

**Code**
- `basic_content/friend/friend_func.cpp`

---

## 18) `union`

**Run**
```bash
bazel run //basic_content/union:union
```

**Key rules**
- Union members share storage; writing one member overwrites the others.
- Size of a union is at least the size of its largest member.

**Code**
- `basic_content/union/union.cpp`

---

## 19) `enum` (old style vs `enum class`)

**Run**
```bash
bazel run //basic_content/enum:tradition_color
bazel run //basic_content/enum:classic_practice
```

**Key points**
- Prefer `enum class` for scoped enums and no implicit conversion to `int`.
- Plain `enum` leaks enumerator names into the surrounding scope.

---

## 20) `::` (scope resolution)

**Run**
```bash
bazel run //basic_content/maohao:maohao
```

**Key idea**
- `::name` refers to the global namespace; `A::name` refers to a member of `A`.

**Code**
- `basic_content/maohao/maohao.cpp`

---

## 21) `decltype`

**Run**
```bash
bazel run //basic_content/decltype:decltype
```

**Key idea**
- `decltype(expr)` gives the type of `expr` at compile time without evaluating it.

**Code**
- `basic_content/decltype/decltype.cpp`

---

## 22) `using`

**Run**
```bash
bazel run //basic_content/using:using_global
bazel run //basic_content/using:using_typedef
bazel run //basic_content/using:using_derived
bazel run //basic_content/using:derived_base
```

**Key uses**
- `using namespace ...` (namespace import — use carefully in headers)
- `using Alias = Type;` (modern typedef)
- `using Base::f;` (bring base overloads into derived scope to avoid name hiding)

---

## 23) Pointers vs references

**Run**
```bash
bazel run //basic_content/pointer_refer:copy_construct
bazel run //basic_content/pointer_refer:effec
```

**Rule of thumb**
- Use references when an argument must be valid and non-null.
- Use pointers when “no value” is a valid state (`nullptr`) or you need reseating.

---

## 24) Macros (`#`, `##`, `\`, and `do { } while (0)`)

**Run**
```bash
bazel run //basic_content/macro:sig_examp
bazel run //basic_content/macro:do_while
```

**Operators**
| Operator | Meaning | Typical macro form |
|---|---|---|
| `#` | stringize an argument | `#x` inside `#define STR(x) ...` |
| `##` | paste tokens together | `a##b` inside `#define CAT(a,b) ...` |
| `\` | continue macro on next line | multi-line `#define` |

**Why `do { } while (0)`**
- Makes multi-statement macros act like a single statement, so they behave correctly under `if (...) MACRO(); else ...`.

**Code**
- `basic_content/macro/sig_examp.cpp`
- `basic_content/macro/do_while.cpp`

---

## Day 1 checklist (covered)

| # | Topic |
|---:|---|
| 1 | `const` |
| 2 | `static` |
| 3 | `this` |
| 4 | `inline` |
| 5 | `sizeof` |
| 6 | function pointers |
| 7 | abstract classes |
| 8 | vptr/vtable |
| 9 | `virtual` |
| 10 | `volatile` |
| 11 | `assert` |
| 12 | bit fields |
| 13 | `extern "C"` |
| 14 | `struct` |
| 15 | C-style “polymorphism” |
| 16 | `explicit` |
| 17 | `friend` |
| 18 | `union` |
| 19 | `enum` |
| 20 | `::` |
| 21 | `decltype` |
| 22 | `using` |
| 23 | pointers vs references |
| 24 | macros |

Ready to move on to the **10‑Day Intensive Practice** section.
