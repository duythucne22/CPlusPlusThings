# Stories About References and Pointers


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 1. References vs pointers


Overall:

| Reference        | Pointer          |
|------------------|------------------|
| Must be initialized | Can be uninitialized |
| Cannot be null   | Can be null      |
| Cannot change target | Can change target |


> **References must be initialized; pointers can remain uninitialized.**

When we define a reference, it must be given an initial value right away, but a pointer does not need to be initialized at declaration.

```cpp
int &r;    // illegal: uninitialized reference
int *p;    // legal, but p is a dangling (wild) pointer; use carefully
```


> **References cannot be null; pointers can.**

Because a reference cannot be null, we do not need to test its validity before use. With pointers, we must first check whether the pointer is null, or the program may crash.

```cpp
void test_p(int* p)
{
    if (p != nullptr)    // must check p before dereferencing
        *p = 3;
    return;
}

void test_r(int& r)
{
    r = 3;    // no null check needed; r always refers to a valid object
    return;
}
```


> **References cannot change target.**

A pointer can be redirected to different objects at any time, while a reference is tied forever to the object it was initialized with. It cannot be “rebound”.

```cpp
int a = 1;
int b = 2;

int &r = a;    // bind reference r to variable a
int *p = &a;   // make pointer p point to a

p = &b;        // p now points to b
r = b;         // r still refers to a; a’s value becomes b’s value
```


## 2. References


### Lvalue references


A normal reference, typically used to represent the **identity** of an object.

### Rvalue references


An rvalue reference is a reference that must bind to an rvalue (a temporary or soon‑to‑be‑destroyed object), and usually represents the **value** of an object.

Rvalue references enable **move semantics** and **perfect forwarding**. Their main purposes are:

- Eliminate unnecessary copies when objects are passed or returned, saving memory and improving performance.  
- Allow cleaner and more explicit generic code (e.g., in template libraries).  


### Reference collapsing


- `X& &`, `X& &&`, `X&& &` all collapse to `X&`.  
- `X&& &&` collapses to `X&&`.  


In C++, references **reduce programmer freedom but improve memory‑access safety and semantic clarity**. For example, requiring initialization means you never need to check a reference for null, which cleans up the code and avoids rampant pointer use. References are also heavily used in two specific contexts:

> **Reference parameters**

Often we use `const`‑qualified references as read‑only parameters. This avoids expensive copies while still providing the same calling syntax as pass‑by‑value.

```cpp
void test(const vector<int> &data)
{
    // ...
}

int main()
{
    vector<int> data{1, 2, 3, 4, 5, 6, 7, 8};
    test(data);
}
```


> **Reference return values**

Overloaded operators in C++ can return references so that the operator can be used in the same way as the built‑in version. For example, `operator[]` usually returns a reference so the element can be assigned to:

```cpp
vector<int> v(10);
v = 10;    // operator[] returns a reference, so v can be modified [cnblogs](https://www.cnblogs.com/scw2901/p/4452620.html)
              // If it returned a pointer, you would need:
*v = 10;   // this syntax is unnatural and confusing [cnblogs](https://www.cnblogs.com/scw2901/p/4452620.html)
```


## 3. Performance difference between pointers and references


Is there any performance difference between pointers and references? To answer this, we must look at the generated assembly code. First, define `test1` using a pointer parameter:

```cpp
void test1(int* p)
{
    *p = 3;    // no null check here, just for testing
    return;
}
```

The corresponding assembly might look like:

```text
(gdb) disassemble 
Dump of assembler code for function test1(int*):
   0x0000000000400886 <+0>:  push   %rbp
   0x0000000000400887 <+1>:  mov    %rsp,%rbp
   0x000000000040088a <+4>:  mov    %rdi,-0x8(%rbp)
=> 0x000000000040088e <+8>:  mov    -0x8(%rbp),%rax
   0x0000000000400892 <+12>: movl   $0x3,(%rax)
   0x0000000000400898 <+18>: nop
   0x0000000000400899 <+19>: pop    %rbp
   0x000000000040089a <+20>: retq   
End of assembler dump.
```

- Instructions 1–2 save the call‑frame context.  
- Instruction 3 stores the pointer `p` (passed in register `rdi`) onto the stack.  
- Instruction 4 loads that stored pointer into `rax`.  
- Instruction 5 writes the immediate value `3` into the memory location pointed to by `rax`—`(%rax)` means “the memory at address `rax`”, i.e., `*p`.  

Next, define `test2` using a reference parameter:

```cpp
void test2(int& r)
{
    r = 3;     // no need to check r for null
    return;
}
```

Its assembly:

```text
(gdb) disassemble 
Dump of assembler code for function test2(int&):
   0x000000000040089b <+0>:  push   %rbp
   0x000000000040089c <+1>:  mov    %rsp,%rbp
   0x000000000040089f <+4>:  mov    %rdi,-0x8(%rbp)
=> 0x00000000004008a3 <+8>:  mov    -0x8(%rbp),%rax
   0x00000000004008a7 <+12>: movl   $0x3,(%rax)
   0x00000000004008ad <+18>: nop
   0x00000000004008ae <+19>: pop    %rbp
   0x00000000004008af <+20>: retq   
End of assembler dump.
```

The assembly code is **identical** to `test1`. This means that at the machine‑code level, pointers and references are implemented the same way. In other words, C++ references are essentially a **syntactic sugar** over pointers: the compiler generates the same instructions for both, but the language imposes stricter rules on references to make them safer and more expressive. [web:98][web:102]


## 4. Summary


C++ introduced references to enhance safety and convenience. The constraints on references (must be initialized, cannot be null, cannot be rebound) make them easier and safer to use than raw pointers, helping to avoid “pointer‑filled” code and improving program stability. At the lower level, both pointers and references are implemented the same way, so there is **no performance difference** between them. The choice is mainly semantic and stylistic: use references where you want an alias to an existing object, and pointers where you need explicit indirection, optional nullability, or pointer arithmetic.

Adapted from: <http://irootlee.com/juicer_pointer_reference/#>