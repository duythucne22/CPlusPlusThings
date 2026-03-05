# Stories About `inline`


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 1. Inline in classes


Declare methods in the header file:

```cpp
class A
{
public:
    void f1(int x);

    /**
     * @brief Functions defined inside the class are implicitly inline.
     *        For a declaration to become an inline function, the `inline` keyword
     *        must be added at the definition/implementation site.
     *
     * @param x
     * @param y
     */
    void Foo(int x, int y) ///< Defined here → implicitly inline!
    {
    };

    void f2(int x); ///< To become inline, the definition must use the `inline` keyword.
};
```


Define inline functions in the implementation file:

```cpp
#include <iostream>
#include "inline.h"

using namespace std;

/**
 * @brief For inline to take effect, the `inline` keyword must appear with the function definition.
 *        `inline` is a "keyword used at the implementation site", not at the declaration site.
 *
 * @param x
 * @param y
 *
 * @return
 */
int Foo(int x, int y);      // function declaration
inline int Foo(int x, int y) // function definition
{
    return x + y;
}

// Add `inline` at the definition; this is the recommended style!
inline void A::f1(int x)
{
}

int main()
{
    cout << Foo(1, 2) << endl;
}

/**
 * Compiler steps for inline functions:
 * 1. Copy the inline function body to each call site.
 * 2. Allocate memory for all local variables inside the inline function.
 * 3. Map the input parameters and return value of the inline function to the caller's stack frame.
 * 4. If the inline function has multiple return points, transform them into branches at the end of the block (using GOTO‑like jumps).
 */
```


Inlining can improve function efficiency, but not all functions should be made inline.  
Inlining trades code bloat (copying) for the elimination of the function‑call overhead, only improving execution speed.  

- If the time spent executing the function body is large compared to the cost of a function call, the efficiency gain from inlining is small.  
- Moreover, every call site of an inline function duplicates the code, increasing the total code size and memory usage.  


Inline functions are **not recommended** in the following cases:

(1) If the function body is long, so that inlining would cause a high memory cost.  
(2) If the function body contains loops, so that the time spent executing the body is much larger than the call overhead.  


## 2. Can virtual functions be inline functions?


- Virtual functions **can** be inline; `inline` is allowed on virtual functions.  
  However, when the virtual function exhibits polymorphism, it **cannot** be inlined.  
- Inlining is a compile‑time hint to the compiler, but virtual dispatch (polymorphism) happens at runtime.  
  The compiler cannot know in advance which derived function will be called, so a virtual call that is truly polymorphic cannot be inlined.  
- The only case where `inline virtual` can actually be inlined is when the compiler knows the exact class of the object (for example, `Base::who()`), which happens only when the compiler sees a concrete object, not a pointer or a reference.  

```cpp
#include <iostream>
using namespace std;

class Base
{
public:
    inline virtual void who()
    {
        cout << "I am Base\n";
    }

    virtual ~Base() {}
};

class Derived : public Base
{
public:
    inline void who()  // implicit inline even without writing `inline`
    {
        cout << "I am Derived\n";
    }
};

int main()
{
    // The virtual function `who()` is called on a concrete object `b` of type `Base`.
    // At compile time the compiler knows which function will be called,
    // so it *may* inline it (but the final decision depends on the compiler).
    Base b;
    b.who();

    // The virtual function is called via a pointer, showing polymorphism.
    // The actual function to call is determined at runtime, so it cannot be inlined.
    Base *ptr = new Derived();
    ptr->who();

    // Because Base has a virtual destructor, `delete` will first call Derived's destructor,
    // then Base's destructor, preventing memory leaks.
    delete ptr;
    ptr = nullptr;

    return 0;
}
```