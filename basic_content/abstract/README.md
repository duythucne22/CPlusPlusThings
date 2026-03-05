# Pure Virtual Functions and Abstract Classes


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 1. Pure virtual functions and abstract classes


In C++, a **pure virtual function** (or abstract function) is a virtual function for which **no implementation is provided**; we only declare it. A pure virtual function is declared by assigning **`= 0`** in its declaration:

```cpp
// Abstract class
class A {
public:
    virtual void show() = 0;  // pure virtual function
    /* Other members */
};
```


- **Pure virtual function**: a virtual function that has no function body.  
- **Abstract class**: a class that contains at least one pure virtual function.  


An abstract class can only be used as a base class to derive new classes; **you cannot create objects of an abstract class**. However, you *can* create pointers and references to abstract classes that actually point to or refer to objects of classes derived from it.


> Code examples: [abstract_base.h](./abstract_base.h), [pure_virtual.cpp](./pure_virtual.cpp)


## 2. Implementing abstract classes


In an abstract class, you are allowed to **call pure virtual functions inside member functions**, but you **cannot call pure virtual functions directly inside the constructor or destructor**.

If a class derives from an abstract class, it must **implement all pure virtual functions** from the base class, or else it will also remain an abstract class.

```cpp
// A is an abstract class
class A {
public:
    virtual void f() = 0;      // pure virtual function
    void g() { this->f(); }
    A() {}                     // constructor
};

class B : public A {
public:
    void f() { cout << "B::f()" << endl; }
                                   // implements the pure virtual function from the abstract base
};
```


> Code example: [abstract.cpp](./abstract.cpp)


## 3. Important points


- [A pure virtual function makes a class abstract](./interesting_facts1.cpp)

```cpp
// An abstract class must contain at least one pure virtual function
class Base {
public:
    virtual void show() = 0;   // pure virtual function
    int getX() { return x; }  // normal member function

private:
    int x;
};
```


- [Pointers and references of an abstract‑class type](./interesting_facts2.cpp)

```cpp
class Derived : public Base {
public:
    void show() { cout << "In Derived \n"; }  // implements the pure virtual function
    Derived() {}                               // constructor
};

int main(void) {
    // Base b;           // error! Cannot create an object of an abstract class
    // Base *b = new Base(); // error!

    Base *bp = new Derived(); // pointer/reference of abstract‑class type → object of a derived class
    bp->show();
    return 0;
}
```


- [If pure virtual functions are not overridden in a derived class, that derived class remains abstract](./interesting_facts3.cpp)

```cpp
// Derived becomes an abstract class as well
class Derived : public Base {
public:
//    void show() {}
};
```


- [Abstract classes can have constructors](./interesting_facts4.cpp)

```cpp
// Abstract class
class Base {
protected:
    int x;
public:
    virtual void fun() = 0;
    Base(int i) { x = i; }   // constructor
};

// Derived class
class Derived : public Base {
    int y;
public:
    Derived(int i, int j) : Base(i) { y = j; }   // constructor
    void fun() { cout << "x = " << x << ", y = " << y; }
};
```


- [Constructors cannot be virtual, but destructors can be virtual destructors](./interesting_facts5.cpp)

```cpp
// Abstract class
class Base {
public:
    Base() { cout << "Constructor: Base" << endl; }
    virtual ~Base() { cout << "Destructor: Base" << endl; }

    virtual void func() = 0;
};

class Derived : public Base {
public:
    Derived() { cout << "Constructor: Derived" << endl; }
    ~Derived() { cout << "Destructor: Derived" << endl; }

    void func() { cout << "In Derived::func()." << endl; }
};
```

> When a base‑class pointer points to a derived‑class object and that object is deleted, we usually want the correct (derived‑class) destructor to be called.  
> If the destructor is not virtual, only the base‑class destructor will be invoked.


## 4. Complete example


An abstract class is implemented through inheritance by derived classes!


> Code example: [derived_full.cpp](./derived_full.cpp)
