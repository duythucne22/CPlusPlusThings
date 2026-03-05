# Stories About `static`


## About the Author


WeChat official account:


![](../img/wechat.jpg)


When used with different kinds of declarations, the `static` keyword has different meanings. We can use `static` to declare:

**Static variables:**  
Variables inside functions, variables inside classes.

**Static class members:**  
Class objects, and functions inside classes.

Now let’s take a closer look at these uses of `static`.


### Static variables


#### Static variables inside functions


When a variable is declared `static`, its memory is allocated **for the entire lifetime of the program**. Even if the function is called multiple times, the space for the static variable is allocated **only once**, and the value from the previous call is preserved and carried over to the next call. This is very useful in C++ (or any C++‑style application) when you need to store state across function calls.

```cpp
#include <iostream>
#include <string>
using namespace std;

void demo() {
    // static variable
    static int count = 0;
    cout << count << " ";

    // value is updated and
    // will be carried to the next
    // function call
    count++;
}

int main() {
    for (int i = 0; i < 5; i++)
        demo();
    return 0;
}
```

Output:

```
0 1 2 3 4
```

You can see in the program above that the variable `count` is declared `static`, so its value persists across function calls. The variable is not re‑initialized each time the function is called.


#### Static variables inside classes


Because a `static` variable is initialized only once and its storage is in a separate static area, **static variables inside a class are shared among all objects**. Different objects cannot have their own separate copies of the same static variable. Also for this reason, static variables cannot be initialized inside constructors.

```cpp
#include <iostream>
using namespace std;

class Apple {
public:
    static int i;

    Apple() {
        // Do nothing
    }
};

int main() {
    Apple obj1;
    Apple obj2;
    obj1.i = 2;
    obj2.i = 3;

    // prints value of i
    cout << obj1.i << " " << obj2.i;
}
```

In the program above, we tried to assign different values to `i` for two objects, but they actually share the same variable. So the static variable inside a class must be explicitly initialized outside the class, using the class name and the scope‑resolution operator, like this:

```cpp
#include <iostream>
using namespace std;

class Apple {
public:
    static int i;

    Apple() {
        // Do nothing
    }
};

int Apple::i = 1;

int main() {
    Apple obj;
    // prints value of i
    cout << obj.i;
}
```

Output:

```
1
```


### Static members


#### Static class objects


Just like variables, when an object is declared `static`, its scope extends throughout the entire program lifetime.

Consider the following program where the object is non‑`static`:

```cpp
#include <iostream>
using namespace std;

class Apple {
    int i;
public:
    Apple() {
        i = 0;
        cout << "Inside Constructor\n";
    }
    ~Apple() {
        cout << "Inside Destructor\n";
    }
};

int main() {
    int x = 0;
    if (x == 0) {
        Apple obj;
    }
    cout << "End of main\n";
}
```

Output:

```cpp
Inside Constructor
Inside Destructor
End of main
```

In the program above, the object is declared non‑`static` inside the `if` block, so its scope is limited to that block. The constructor runs when the object is created, and the destructor runs immediately when the block ends, because the object is local to that block.

If we instead declare the object `static`, the behavior changes:

```cpp
#include <iostream>
using namespace std;

class Apple {
    int i;
public:
    Apple() {
        i = 0;
        cout << "Inside Constructor\n";
    }
    ~Apple() {
        cout << "Inside Destructor\n";
    }
};

int main() {
    int x = 0;
    if (x == 0) {
        static Apple obj;
    }
    cout << "End of main\n";
}
```

Output:

```
Inside Constructor
End of main
Inside Destructor
```

You can clearly see the difference: the destructor is called after `main` finishes. This is because the scope of a static object extends for the entire program lifetime.


#### Static functions inside classes


Like static data members, static member functions do not depend on class objects. We are allowed to call a static member function through an object using `.` (e.g., `obj.func()`), but it is recommended to call it using the class name and the scope‑resolution operator.

A static member function can access only static data members or other static member functions; it cannot access non‑static data members or non‑static member functions.

```cpp
#include <iostream>
using namespace std;

class Apple {
public:
    // static member function
    static void printMsg() {
        cout << "Welcome to Apple!";
    }
};

// main function
int main() {
    // invoking a static member function
    Apple::printMsg();
}
```

Output:

```
Welcome to Apple!
```


### Restricting visibility (file‑scope linkage)

`static` can also be used to restrict the visibility of a name to the current translation unit (similar to an anonymous namespace). See issue: https://github.com/Light-City/CPlusPlusThings/issues/142

```cpp
// source1.cpp
extern void sayHello();
const char* msg = "Hello World!\n";
int main() {
    sayHello();
    return 0;
}

// source2.cpp
#include <cstdio>
extern char* msg;
void sayHello() {
    printf("%s", msg);
}
```

With `g++`, these two files compile and run correctly, printing `Hello World!`. However, if `msg` in `source1.cpp` is marked `static`, the linker produces an “undefined reference to 'msg'” error:

```cpp
// source1.cpp
extern void sayHello();
static const char* msg = "Hello World!\n";
int main() {
    sayHello();
    return 0;
}
```