# Friend Functions and Friend Classes


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 0. Overview


Friendship provides a mechanism that allows **ordinary functions** or **member functions of another class** to access private or protected members of a class. There are two main forms of friendship:

1. **Friend function**: an ordinary function that accesses private or protected members of a class.  
2. **Friend class**: a class whose member functions access private or protected members of another class.

Pros:

- Increases runtime efficiency, since the friend can access data directly without going through normal accessors.

Cons:

- Breaks the **encapsulation** and **data transparency** of the class.

Summary:

- Can access private members.  
- Breaks encapsulation.  
- Friendship is **not inheritable**.  
- Friendship is **not transitive**.  
- Friendship is **unidirectional** (B is friend of A does not imply A is friend of B).  
- The form and number of friend declarations on a class are not restricted.  


## 1. Friend functions


A friend function is declared inside the class declaration (in any access section), but defined outside the class.

```cpp
friend <type> <friend_function_name>(<parameter_list>);
```

Note that a friend function is just an **ordinary function**, not a member function of the class. It can be called from anywhere and accesses the class’s private or protected members through an object name.

Example code: [friend_func.cpp](friend_func.cpp)

```cpp
#include <iostream>
using namespace std;

class A
{
public:
    A(int _a) : a(_a) {}
    friend int geta(A &ca);   ///< friend function
private:
    int a;
};

int geta(A &ca)
{
    return ca.a;
}

int main()
{
    A a(3);
    cout << geta(a) << endl;
    return 0;
}
```


## 2. Friend classes


A friend class is declared inside the class that grants friendship, but its implementation is outside.

```cpp
friend class <friend_class_name>;
```

If class B is a friend of class A, then class B can access the private and protected members of class A directly.

Example code: [friend_class.cpp](friend_class.cpp)

```cpp
#include <iostream>
using namespace std;

class A
{
public:
    A(int _a) : a(_a) {}
    friend class B;
private:
    int a;
};

class B
{
public:
    int getb(A ca) {
        return ca.a;
    }
};

int main()
{
    A a(3);
    B b;
    cout << b.getb(a) << endl;
    return 0;
}
```


## 3. Important notes


- **Friendship is not inherited.**  
  If class B is a friend of class A, and class C inherits from class A, class B still cannot directly access private or protected members of class C.

- **Friendship is not transitive.**  
  If class B is a friend of class A, and class C is a friend of class B, class C cannot directly access private or protected members of class A. There is no concept of “the friend of a friend” in C++.  