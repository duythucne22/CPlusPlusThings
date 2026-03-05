## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


## 1. `volatile`


A variable qualified with `volatile` can trigger some **observable side effects** when it is read or written. These observable side effects are determined by factors **outside the program itself**.


## 2. Uses of `volatile`


### (1) Hardware registers of parallel or I/O devices (e.g., status registers)

Suppose you want to initialize a hardware device whose specific register is located at address `0xff800000`:

```cpp
int *output = (unsigned int *)0xff800000;  // define an I/O port
int init(void)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        *output = i;
    }
}
```

After optimization, the compiler may realize that all the loop iterations except the last one have no effect on the final value of `*output`, which is `9`. So it optimizes the code as if you had written:

```cpp
int init(void)
{
    *output = 9;
}
```

If the device initialization must be done in the exact sequence shown above, this optimization would break the program. In contrast, if you are repeatedly reading from such a port rather than writing to it, the same problem occurs: the compiler might optimize away all but one read operation, even though the code *appears* correct from a C / C++ semantics perspective. In such cases, `volatile` should be used to inform the compiler that this variable is “unstable” and must not be optimized away.


### (2) Variables accessed inside an interrupt service routine (ISR)

```cpp
static int i = 0;

int main()
{
    while (1)
    {
        if (i) dosomething();
    }
}

/* Interrupt service routine */
void ISR()
{
    i = 1;
}
```

The intent of this example is that when an interrupt occurs, the ISR (`ISR`) sets `i` to `1`, so that `main` will call `dosomething()`. However, since the compiler sees no modifications to `i` inside `main`, it may optimize the code to read `i` once into a register and then only use that register copy in the loop condition. As a result, `dosomething()` may never be called. By declaring `i` as `volatile`, the compiler is forced to read `i` from memory every time it is used, ensuring that changes to `i` made by the ISR are immediately visible in `main`.


### (3) Variables shared among multiple threads in a multithreaded application

When multiple threads share a variable and one thread can modify it, the variable should be declared `volatile`. This prevents the compiler from optimizing repeated accesses by loading the variable into a CPU register and keeping only that copy. If a thread changes the variable’s value in memory, other threads may continue to see the stale cached value and cause incorrect behavior. `volatile` forces the compiler to always read the value from memory and not rely on a cached copy.

Example:

```cpp
volatile bool bStop = false;  // bStop is a shared global variable

// Thread 1
void threadFunc1()
{
    ...
    while (!bStop)
    {
        ...
    }
}

// Thread 2 terminates the loop in thread 1
void threadFunc2()
{
    ...
    bStop = true;
}
```

To stop `threadFunc1`’s loop from thread `threadFunc2`, `bStop` must be declared `volatile`. Otherwise, `bStop` may be cached in a register inside the loop, and the condition `!bStop` will never see the update, creating an infinite loop. With `volatile`, each test reads `bStop` from memory, so the stop signal is detected promptly.


Understanding `volatile` usage is a good way to distinguish general C/C++ programmers from embedded‑systems developers. Embedded developers regularly work with hardware registers, interrupts, and RTOS kernels, all of which often require `volatile` variables. Not understanding `volatile` can lead to severe bugs and hard‑to‑diagnose failures.


## 3. Common `volatile` questions


These questions help assess whether a candidate really understands `volatile`.


### (1) Can a parameter be both `const` and `volatile`? Why?

Yes. An example is a **read‑only status register**. It is `volatile` because its value can change unexpectedly (e.g., due to hardware). It is `const` because the program should not attempt to modify it through that variable declaration.


### (2) Can a pointer be `volatile`? Why?

Yes, although this is not common. An example is when an interrupt service routine modifies a pointer to a buffer:

```cpp
volatile int *buf_ptr;
```

In this case, both the pointer itself and the value it points to may be changed by factors outside the normal flow of the program, so the `volatile` qualifier is appropriate.


### (3) What is wrong with this function?

```cpp
int square(volatile int *ptr)
{
    return *ptr * *ptr;
}
```

This code is intended to return the square of the value pointed to by `ptr`. However, because `ptr` points to a `volatile`‑qualified object, the compiler must read `*ptr` each time it appears. So it may generate something like:

```cpp
int square(volatile int *ptr)
{
    int a, b;
    a = *ptr;
    b = *ptr;
    return a * b;
}
```

Since `*ptr` could change between the two reads, `a` and `b` may be different, and the result will not be `*ptr * *ptr` as expected. The correct version reads the value once and then squares that copy:

```cpp
long square(volatile int *ptr)
{
    int a = *ptr;
    return a * a;
}
```


## 4. How to use `volatile`


- The `volatile` keyword is a type qualifier. A variable declared `volatile` may be changed by factors unknown to the compiler (such as the operating system, hardware, or other threads). Therefore, `volatile` tells the compiler not to optimize accesses to such variables.

- Each access to a `volatile`‑qualified variable must be performed by reading from (or writing to) memory; for non‑`volatile` variables the compiler may keep a copy in a CPU register.

- A variable can be both `const` and `volatile` (for example, a read‑only status register).

- A pointer can be declared `volatile` (e.g., `volatile int *`), and so can the object it points to (e.g., `volatile int *volatile` for a pointer to a volatile integer whose address is also volatile).

Code to study:

- [noopt_vola.cpp](./noopt_vola.cpp)
- [volatile.cpp](./volatile.cpp)