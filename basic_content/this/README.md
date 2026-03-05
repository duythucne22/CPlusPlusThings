# Stories About the `this` Pointer


## About the Author


WeChat official account:


![](../img/wechat.jpg)


## 1. `this` pointer


I believe many of you are learning Python, and in Python there is `self`. By analogy, the corresponding concept in C++ is the `this` pointer. Let’s now analyze in depth how `this` is used in classes.


First, let’s talk about the role of the `this` pointer:

(1) The `this` pointer of an object is not part of the object itself and does not affect the result of `sizeof(object)`.

(2) The scope of `this` is inside the class. When you access non‑static class members inside a class’s non‑static member function, the compiler automatically passes the address of the object itself as an implicit parameter to the function. In other words, even if you don’t explicitly write `this`, the compiler inserts it during compilation as an implicit parameter of the non‑static member function. All member accesses are then implemented via `this`.


Next, typical uses of the `this` pointer:

(1) When a non‑static member function needs to return the object itself, use `return *this` directly.

(2) When a parameter has the same name as a member variable, write `this->n = n` (you cannot write `n = n`).

Moreover, online you might see people say `this` is compiled into `A *const` or `A const *`. Which one is it? We can analyze this with a debugger example below.

Here is a simple example:

```cpp
#include <iostream>
#include <cstring>

using namespace std;

class Person {
public:
    typedef enum {
        BOY = 0,
        GIRL
    } SexType;

    Person(char *n, int a, SexType s) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        age = a;
        sex = s;
    }

    int get_age() const {
        return this->age;
    }

    Person& add_age(int a) {
        age += a;
        return *this;
    }

    ~Person() {
        delete [] name;
    }

private:
    char *name;
    int age;
    SexType sex;
};

int main() {
    Person p("zhangsan", 20, Person::BOY);
    cout << p.get_age() << endl;
    cout << p.add_age(10).get_age() << endl;
    return 0;
}
```

This simple program should be clear: we define a class, initialize it via a constructor, then get the person’s age, update it, and get it again.

To verify what form `this` takes, we can set a breakpoint at `add_age` and run the program:

![thiscontrust](./img/thiscontrust.png)

![genthis](./img/genthis.png)

From this, we see the compiler has in fact turned `this` into `A* const`, not `A const*`.

Next, there is also a `const` member function above. If we set a breakpoint at `get_age`, we get the following:

![constthis](./img/constthis.png)

Here, the compiler changes `this` to `const A* const`. This also makes sense: because `get_age` is a `const` member function, it can only read `const` members and cannot modify any data member. Therefore the target of `this` must be `const`; that is, `const A*`. And since `this` itself is always a `const` pointer (its address cannot change), the full type becomes `const A* const`.


**Summary:** The `this` pointer is implicitly constructed before a member function starts executing and is cleared after the function finishes. In other words:

- `get_age` would be interpreted by the compiler as `get_age(const A* const this)`.
- `add_age` would be interpreted as `add_age(A* const this, int a)`.

In C++, the only difference between a class and a struct is that class members are `private` by default while struct members are `public` by default. `this` is a pointer to the class; if you wrote it as a struct, `this` would be a pointer to that struct instead.