# Enums from Basic to Advanced


## About the Author


Personal WeChat official account:


![WeChat](../img/wechat.jpg)


## Traditional behavior


Classic `enum` has several problems:

- **Unscoped**: enum names are in the global scope, so they can easily cause naming conflicts. For example, this code fails to compile:

```cpp
enum Color
{
    RED,
    BLUE
};
enum Feeling
{
    EXCITED,
    BLUE
};

int main()
{
    Color a = BLUE; // error: BLUE is ambiguous
    Feeling b = EXCITED;
    std::cout << a << ":" << b << std::endl;
    return 0;
}
```

- **Implicit conversion to `int`**  
- **No explicit underlying type**: the actual integer type used to store enum values cannot be controlled, so forward‑declaration of enum types is not supported.

See full implementation: [tradition_color.cpp](tradition_color.cpp)


## Classic practice


A common trick to avoid naming conflicts is to add a prefix to all enum constants, e.g., `COLOR_BLUE` and `FEELING_BLUE`. In C, this is often unavoidable. In C++, however, programmers prefer cleaner solutions.

One is to wrap the `enum` inside a **namespace**:

```cpp
namespace Color
{
    enum Type
    {
        RED = 15,
        YELLOW,
        BLUE
    };
};
```

Now you can write `Color::Type c = Color::RED;`. If you add `using namespace Color;`, you can abbreviate to `RED`, but the namespace can still be extended later, so the scoping is not strict.

A stronger way is to wrap the `enum` inside a **class** or **struct**, which genuinely limits its scope and cannot be arbitrarily extended elsewhere. Here we use a `struct` because the constants should be publicly accessible:

```cpp
struct Color1
{
    enum Type
    {
        RED = 102,
        YELLOW,
        BLUE
    };
};
```

See implementation: [classic_practice.cpp](classic_practice.cpp)


## C++11 enum classes


The above solves the scoping problem but not the implicit conversion or type‑control issues. C++11 introduced **“enum classes”** (`enum class`) to fix this:

- **Scoped enumerators** (no longer global scope).  
- **No implicit conversion** to other types.

```cpp
/**
 * @brief C++11 enum class
 * Same as enum class Color2 : int
 */
enum class Color2
{
    RED = 2,
    YELLOW,
    BLUE
};
Color2 c2 = Color2::RED;
cout << static_cast<int>(c2) << endl; // cast required
```

- **Control underlying type**:

```cpp
enum class Color3 : char;  // forward declaration

// definition
enum class Color3 : char
{
    RED = 'r',
    BLUE
};
char c3 = static_cast<char>(Color3::RED);
```

See full implementation: [classic_practice.cpp](classic_practice.cpp)


## Enum types inside classes


Sometimes you want constants to be tied to a class, not global. Global `#define` macros are bad for this, and `const` data members are not quite right either.

A `const` data member is constant only for a particular object, not for the whole class. Different objects can have different `const` values. Also, you cannot initialize `const` data members in the class body before C++11:

```cpp
class A
{
    const int SIZE = 100;   // error: cannot initialize const here
    int array[SIZE];        // error: SIZE unknown
};
```

Instead, you must initialize in the constructor’s initializer list:

```cpp
class A
{
    A(int size);
    const int SIZE;
};
A::A(int size) : SIZE(size) { }
A a(100);  // a.SIZE = 100
A b(200);  // b.SIZE = 200
```

For a **class‑wide constant** that is the same across all instances, use an **enum inside the class**:

```cpp
class Person {
public:
    typedef enum {
        BOY = 0,
        GIRL
    } SexType;
};
// Access via Person::BOY or Person::GIRL.
```

Enum constants do not occupy per‑object storage; they are resolved at compile time. The downside is that their underlying type is integer, with a limited maximum value, and they cannot represent floating‑point constants.