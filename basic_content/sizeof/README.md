# Class Size Calculation


Let’s start with a summary, and then move on to concrete examples for practice.

- An empty class has a size of **1 byte**.  
- In a class, virtual functions, member functions (both static and non‑static), and static data members **do not contribute to the size of class objects**.  
- For a class with virtual functions, no matter how many virtual functions there are, only **one virtual pointer (vptr)** is counted in the size.  
- In **ordinary (non‑virtual) inheritance**, the derived class inherits all base‑class members; the total size must be computed with **padding due to alignment**.  
- In **virtual‑function inheritance** (single or multiple inheritance), the derived class still inherits the base‑class `vptr` (4 bytes on 32‑bit systems, 8 bytes on 64‑bit systems).  
- In **virtual inheritance**, the derived class inherits the base‑class `vptr`.  


## 1. Rule 1


```cpp
/**
 * @file blackclass.cpp
 * @brief The size of an empty class is 1 byte.
 * @author Guangcheng
 * @version v1
 * @date 2019-07-21
 */
#include <iostream>
using namespace std;

class A {};

int main()
{
    cout << sizeof(A) << endl;
    return 0;
}
```


## 2. Rule 2


```cpp
/**
 * @file static.cpp
 * @brief Static data members
 * Static data members are placed by the compiler in global program storage.
 * They are class members, but they do not affect the size of class objects.
 * No matter how many instances of the class exist, or how many derived classes
 * are created, there is only one instance of the static data member.
 * Once declared, a static data member already exists.
 * @author Guangcheng
 * @version v1
 * @date 2019-07-21
 */
#include <iostream>
using namespace std;

class A
{
public:
    char b;
    virtual void fun() {}
    static int c;
    static int d;
    static int f;
};

int main()
{
    /**
     * @brief 16 bytes: alignment, static variables do not affect class size,
     *        size of vptr = 8 bytes.
     */
    cout << sizeof(A) << endl;
    return 0;
}
```


## 3. Rule 3


```cpp
/**
 * @file morevir.cpp
 * @brief For a class with virtual functions, no matter how many virtual
 *        functions exist, there is only one virtual pointer (vptr) in the size.
 * @author Guangcheng
 * @version v1
 * @date 2019-07-21
 */
#include <iostream>
using namespace std;

class A {
    virtual void fun();
    virtual void fun1();
    virtual void fun2();
    virtual void fun3();
};

int main()
{
    cout << sizeof(A) << endl; // 8
    return 0;
}
```


## 4. Rule 4 and Rule 5


```cpp
/**
 * @file geninhe.cpp
 * @brief 1. Ordinary single inheritance:
 *        size = base class size + derived class size (with padding due to alignment).
 *        Note: data members are laid out in the order of declaration; access
 *        specifiers do not matter, only the declaration order matters.
 * 2. Virtual single inheritance:
 *    the derived class inherits the base class vptr.
 * @author Guangcheng
 * @version v1
 * @date 2019-07-21
 */

#include <iostream>
using namespace std;

class A
{
public:
    char a;
    int b;
};

/**
 * @brief Now B’s layout:
 *        char a
 *        int b
 *        short a
 *        long b
 *        With alignment: 4+4+8+8 = 24
 *        OR after compiler optimization:
 *        char a
 *        short a
 *        int b
 *        long b
 *        With alignment: 2+2+4+8 = 16
 */
class B : A
{
public:
    short a;
    long b;
};

/**
 * @brief Interpreting A’s members separately:
 *        char a → 1 byte, int b → 4 bytes.
 *        So 1 + (3 padding) + 4 + 1 + (3 padding) = 12 bytes.
 *        Parentheses indicate padding bytes.
 */
class C
{
    A a;
    char c;
};

class A1
{
    virtual void fun() {}
};

class C1 : public A1
{
};

int main()
{
    cout << sizeof(A) << endl;  // 8
    cout << sizeof(B) << endl;  // 16 or 24
    cout << sizeof(C) << endl;  // 12

    /**
     * @brief For virtual single‑inheritance, the derived class inherits the base’s vptr;
     *        so the size is 8 bytes.
     */
    cout << sizeof(C1) << endl; // 8
    return 0;
}
```


## 5. Rule 6


```cpp
/**
 * @file virnhe.cpp
 * @brief Virtual inheritance
 * @author Guangcheng
 * @version v1
 * @date 2019-07-21
 */

#include <iostream>
using namespace std;

class A
{
    virtual void fun() {}
};

class B
{
    virtual void fun2() {}
};

class C : virtual public A, virtual public B
{
public:
    virtual void fun3() {}
};

int main()
{
    /**
     * @brief 8 8 16:
     *        In multiple virtual inheritance of classes with virtual functions,
     *        the derived class inherits all virtual‑function vptrs.
     */
    cout << sizeof(A) << " " << sizeof(B) << " " << sizeof(C) << endl;

    return 0;
}
```