# Stories About `using`


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## Basic usage


Local and global `using`, with detailed behavior shown in the examples below:

```cpp
#include <iostream>
#define isNs1 1
//#define isGlobal 2
using namespace std;

void func()
{
    cout << "::func" << endl;
}

namespace ns1 {
    void func()
    {
        cout << "ns1::func" << endl;
    }
}

namespace ns2 {
#ifdef isNs1
    using ns1::func;    /// function from ns1
#elif isGlobal
    using ::func;       /// function from global scope
#else
    void func()
    {
        cout << "other::func" << endl;
    }
#endif
}

int main()
{
    /**
     * This is why c++ uses <cmath> instead of the C <math.h> header:
     * precision and control over which namespace is used.
     */
    ns2::func();   // calls different versions of func() depending on which macro is defined
    return 0;
}
```

Full code: [using_global.cpp](using_global.cpp)


## Changing accessibility


```cpp
class Base {
public:
    std::size_t size() const { return n; }
protected:
    std::size_t n;
};

class Derived : private Base {
public:
    using Base::size;   // promote size to public in Derived
protected:
    using Base::n;      // keep n as protected in Derived
};
```

Class `Derived` privately inherits from `Base`. For `Derived`, `n` and `size()` become private members. By using `using` declarations, you can change their access level: in this example, `size()` becomes accessible as `public` and `n` as `protected`.

Full code: [derived_base.cpp](derived_base.cpp)


## Function overloading in inheritance


In inheritance, a derived class can override zero or more overloaded function versions. Once a derived class defines one overload, the other base‑class overloads become **hidden** and thus not visible in the derived class.

If you want to change the behavior of one overloaded version in the derived class but still keep the others visible, you must otherwise redeclare all overloads, which is cumbersome.

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    void f() {
        cout << "f()" << endl;
    }
    void f(int n) {
        cout << "Base::f(int)" << endl;
    }
};

class Derived : private Base {
public:
    using Base::f;        // bring all overloads of f into Derived scope
    void f(int n) {
        cout << "Derived::f(int)" << endl;
    }
};

int main()
{
    Base b;
    Derived d;
    d.f();      // calls Base::f()
    d.f(1);     // calls Derived::f(int)
    return 0;
}
```

Here, the `using Base::f;` declaration in the derived class brings **all overloads** of `f` into the derived class scope. Because it names the function without specifying a parameter list, every overload of `Base::f` becomes visible. The derived class then only needs to override the specific version it wants to change; the rest remain usable without redeclaration.

Full code: [using_derived.cpp](using_derived.cpp)


## `using` as a replacement for `typedef`


In C it is common to write `typedef A B` to give a type `A` an alias `B`:

```cpp
typedef vector<int> V1;
using V2 = vector<int>;
```

The two are equivalent, but `using` is more readable and is the preferred C++‑style way to create type aliases. The second form uses the `using` declaration, which replaces `typedef` and is more natural in C++ templates and complex types.

Full code: [using_typedef.cpp](using_typedef.cpp)