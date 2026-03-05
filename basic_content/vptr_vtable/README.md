# Demystifying C++ Virtual‑Function vptr and vtable


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)




## 1. Basic theory


To implement virtual functions, C++ uses a special form of late (dynamic) binding called a **virtual table**. The virtual table is essentially a lookup table used to resolve function calls at runtime in a dynamic binding scheme. Virtual tables are also known by other names such as **“vtable”**, **“virtual function table”**, **“virtual method table”**, or **“dispatch table”**.


A virtual table is actually quite simple, although it can sound complicated in words. First, **every class that uses virtual functions (or inherits from a class that uses virtual functions) has its own virtual table**. This table is just a static array set up by the compiler at compile time. The virtual table contains one entry for each virtual function that can be called by objects of that class. Each entry in the table is just a function pointer pointing to the most derived version of that function accessible to the class.


Second, the compiler also adds a hidden pointer to the base class, which we call the **vptr**. The vptr is set automatically when a class instance is created so that it points to that class’s virtual table. Unlike the `this` pointer, which is essentially a compiler‑generated function parameter used to resolve self‑references, the vptr is a real pointer stored as part of the object.


Consequently, each object of a class with virtual functions becomes larger by the size of one pointer. This also means that the vptr is inherited by derived classes, which is important for polymorphism. [web:31][web:33][web:34][web:35]


## 2. Implementation and internal structure


Next, we’ll look at both automatic and manual manipulation of the vptr to obtain addresses and manually call virtual functions.


Before diving into the code, here is a simple call‑layout diagram for easier understanding:

![base](./img/base.jpg)


The code follows standard Doxygen‑style comments; after reading it you should be clear, and if not, you can leave a comment! [web:34][web:36]


```cpp
/**
 * @file vptr1.cpp
 * @brief C++ virtual‑function vptr and vtable
 * Compile: g++ -g -o vptr vptr1.cpp -std=c++11
 * @author Guangcheng
 * @version v1
 * @date 2019-07-20
 */

#include <iostream>
#include <stdio.h>
using namespace std;

/**
 * @brief Function pointer type
 */
typedef void (*Fun)();

/**
 * @brief Base class
 */
class Base
{
public:
    Base() {}
    virtual void fun1()
    {
        cout << "Base::fun1()" << endl;
    }
    virtual void fun2()
    {
        cout << "Base::fun2()" << endl;
    }
    virtual void fun3() {}
    ~Base() {}
};

/**
 * @brief Derived class
 */
class Derived : public Base
{
public:
    Derived() {}
    void fun1()
    {
        cout << "Derived::fun1()" << endl;
    }
    void fun2()
    {
        cout << "DerivedClass::fun2()" << endl;
    }
    ~Derived() {}
};

/**
 * @brief Get vptr address and virtual‑function address.
 *        vptr points to a memory region that stores virtual‑function addresses;
 *        this region is what we call the virtual table (vtable).
 *
 * @param obj     pointer to an object (interpreted as void*)
 * @param offset  index into the vtable (0 for first virtual function, etc.)
 *
 * @return function pointer to the virtual function at the given offset
 */
Fun getAddr(void* obj, unsigned int offset)
{
    cout << "=======================" << endl;
    // On a 64‑bit system the vptr is 8 bytes wide.
    // Read the first 8 bytes of the object as the vptr.
    void* vptr_addr = (void *)*(unsigned long *)obj;
    printf("vptr_addr:%p\n", vptr_addr);

    /**
     * @brief Access the virtual table via vptr_addr.
     *        Each virtual‑function pointer in the vtable is 8 bytes on a 64‑bit compiler.
     *        So by casting vptr_addr to (unsigned long*) we can index into the table,
     *        and vptr_addr + offset gives the address of the virtual function.
     */
    void* func_addr = (void *)*((unsigned long *)vptr_addr + offset);
    printf("func_addr:%p\n", func_addr);
    return (Fun)func_addr;
}

int main(void)
{
    Base ptr;
    Derived d;
    Base *pt = new Derived();   // base pointer to derived instance
    Base &pp = ptr;             // base reference to base instance
    Base &p = d;                // base reference to derived instance

    cout << "基类对象直接调用" << endl;                    // direct call on base object
    ptr.fun1();

    cout << "基类引用指向基类实例" << endl;                // base ref to base instance
    pp.fun1();

    cout << "基类指针指向派生类实例并调用虚函数" << endl; // base ptr to derived, virtual call
    pt->fun1();

    cout << "基类引用指向派生类实例并调用虚函数" << endl; // base ref to derived, virtual call
    p.fun1();

    // Manually traverse vptr and vtable
    Fun f1 = getAddr(pt, 0);
    (*f1)();
    Fun f2 = getAddr(pt, 1);
    (*f2)();

    delete pt;
    return 0;
}
```


Output:

```
基类对象直接调用
Base::fun1()
基类引用指向基类实例
Base::fun1()
基类指针指向派生类实例并调用虚函数
Derived::fun1()
基类引用指向派生类实例并调用虚函数
Derived::fun1()
=======================
vptr_addr:0x401130
func_addr:0x400ea8
Derived::fun1()
=======================
vptr_addr:0x401130
func_addr:0x400ed4
DerivedClass::fun2()
```


We can see that C++ dynamic polymorphism is implemented via virtual functions. In simple terms, thanks to the `virtual` keyword, a base pointer that points to a derived‑class object can call the derived‑class’s version of the overridden function. For example, when the base pointer `pt` points to a `Derived` instance and calls the virtual function `fun1()`, the code can be simplified to:

```cpp
Base *pt = new Derived();   // base pointer to derived instance
cout << "基类指针指向派生类实例并调用虚函数" << endl;
pt->fun1();
```

The process is:

1. The compiler recognizes that `fun1()` is virtual.  
2. It uses `pt->vptr` to obtain the `Derived` class’s virtual table.  
3. It consults the `Derived` virtual table to decide which version of `fun1()` to call.  
4. Here it finds `Derived::fun1()`, so `pt->fun1()` is effectively resolved to `Derived::fun1()`.

In addition, the code also shows how to manually retrieve the vptr address and call the functions in the vtable. We can verify that these manually retrieved addresses match the ones used automatically when the program calls `pt->fun1()` and similar virtual calls. [web:31][web:33][web:34]


To do this, we use `gdb` and compile with the `-g` flag.

Enter `gdb vptr` to start the debugger, then set a breakpoint on `Derived::fun1` with `b Derived::fun1`, and run with `r` until the breakpoint is hit. At that point, to inspect the memory address of the function, use `disassemble fun1`. You will see an assembly address such as `0x0000000000400ea8`, which matches the `func_addr` printed by our manual lookup; a similar check for `fun2` shows the same vtable‑based address, thereby proving our code is correct. [web:31][web:33][web:34]


GDB debugging output:

```cpp
(gdb) b Derived::fun1
Breakpoint 1 at 0x400eb4: file vptr1.cpp, line 23.
(gdb) r
Starting program: /home/light/Program/CPlusPlusThings/virtual/pure_virtualAndabstract_class/vptr 
基类对象直接调用
Base::fun1()
基类引用指向基类实例
Base::fun1()
基类指针指向派生类实例并调用虚函数

Breakpoint 1, Derived::fun1 (this=0x614c20) at vptr1.cpp:23
23              cout << "Derived::fun1()" << endl;
(gdb) disassemble fun1
Dump of assembler code for function Derived::fun1():
   0x0000000000400ea8 <+0>: push   %rbp
   0x0000000000400ea9 <+1>: mov    %rsp,%rbp
   0x0000000000400eac <+4>: sub    $0x10,%rsp
   0x0000000000400eb0 <+8>: mov    %rdi,-0x8(%rbp)
=> 0x0000000000400eb4 <+12>:    mov    $0x401013,%esi
   0x0000000000400eb9 <+17>:    mov    $0x602100,%edi
   0x0000000000400ebe <+22>:    callq  0x4009d0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
   0x0000000000400ec3 <+27>:    mov    $0x400a00,%esi
   0x0000000000400ec8 <+32>:    mov    %rax,%rdi
   0x0000000000400ecb <+35>:    callq  0x4009f0 <_ZNSolsEPFRSoS_E@plt>
   0x0000000000400ed0 <+40>:    nop
   0x0000000000400ed1 <+41>:    leaveq 
   0x0000000000400ed2 <+42>:    retq   
End of assembler dump.
(gdb) disassemble fun2
Dump of assembler code for function Derived::fun2():
   0x0000000000400ed4 <+0>: push   %rbp
   0x0000000000400ed5 <+1>: mov    %rsp,%rbp
   0x0000000000400ed8 <+4>: sub    $0x10,%rsp
   0x0000000000400edc <+8>: mov    %rdi,-0x8(%rbp)
   0x0000000000400ee0 <+12>:    mov    $0x401023,%esi
   0x0000000000400ee5 <+17>:    mov    $0x602100,%edi
   0x0000000000400eea <+22>:    callq  0x4009d0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
   0x0000000000400eef <+27>:    mov    $0x400a00,%esi
   0x0000000000400ef4 <+32>:    mov    %rax,%rdi
   0x0000000000400ef7 <+35>:    callq  0x4009f0 <_ZNSolsEPFRSoS_E@plt>
   0x0000000000400efc <+40>:    nop
   0x0000000000400efd <+41>:    leaveq 
   0x0000000000400efe <+42>:    retq   
End of assembler dump.
```