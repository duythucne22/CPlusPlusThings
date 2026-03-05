## About the author


Personal WeChat official account:


![](../img/wechat.jpg)


## What is a bit field?


A **bit field** (or **bit‑field**) is a kind of data structure that packs data as individual bits, enabling compact storage and allowing the programmer to manipulate particular bits within the structure. One advantage of bit fields is that they can save memory space, which is especially important when a program uses thousands or even millions of such data units. A second advantage is that bit fields make it easy to access parts of an integer value, often simplifying the source code. The main drawback is that bit‑field layout and behavior are **machine‑ and platform‑dependent**, so bit fields are essentially **non‑portable** across different systems.


- The memory layout of bit fields is platform‑specific.  
- The type of a bit field must be an integral type or an enumeration type; the behavior of signed‑type bit fields is implementation‑defined.  
- The address‑of operator (`&`) cannot be applied to a bit field; no pointer can point directly to a class bit field.  


## Using bit fields


Bit fields are usually declared inside a `struct`, which gives each bit‑field member a name and specifies its width:

```text
struct bit_field_name
{
    type member_name : width;
};
```


| Element        | Description                                                |
|----------------|------------------------------------------------------------|
| bit_field_name | Name of the bit‑field structure                            |
| type           | Type of the bit‑field member; must be `int`, `signed int`, or `unsigned int` |
| member_name    | Name of the bit‑field member                               |
| width          | Number of bits allocated to this member                    |


For example, declare the following bit‑field structure:

```text
struct _PRCODE
{
    unsigned int code1: 2;
    unsigned int code2: 2;
    unsigned int code3: 8;
};
struct _PRCODE prcode;
```

This definition makes `prcode` contain two 2‑bit fields and one 8‑bit field. You can assign values using normal structure member syntax:

```text
prcode.code1 = 0;
prcode.code2 = 3;
prcode.code3 = 102;
```

When assigning values, ensure the value fits within the bit‑field width. For example, `code3` is an 8‑bit field, so its valid range is `[0, 255]` (since \(2^8 = 256\)).


## Bit‑field size and alignment


### Bit‑field size


For example, consider this bit‑field struct:

```text
struct box 
{
    unsigned int a: 1;
    unsigned int   : 3;
    unsigned int b: 4;
};
```

The unnamed bit field in the middle occupies 3 bits and is used only as padding with no semantic meaning. The total bit width of the struct is 8 bits. However, C uses an `unsigned int` as the fundamental unit of a bit field, so even if a structure’s only member is 1 bit, the size of the structure is still equal to the size of an `unsigned int`. On some systems an `unsigned int` is 16 bits, while on x86 it is typically 32 bits. The following examples assume `unsigned int` is 32 bits unless otherwise stated.


### Bit‑field alignment


A bit field is not allowed to span across two `unsigned int` boundaries. If the total number of bits declared would exceed the size of one `unsigned int`, the compiler will automatically move the next bit‑field member into the next `unsigned int` unit to keep alignment.

For example:

```text
struct stuff 
{
    unsigned int field1: 30;
    unsigned int field2: 4;
    unsigned int field3: 3;
};
```

Here `field1 + field2 = 34` bits, which exceeds 32 bits. The compiler will place `field2` in the next `unsigned int` unit, leaving a 2‑bit gap between `field1` and `field2`. `field3` follows immediately after `field2`, so the total size of the struct is now `2 * 32 = 64` bits.

Such padding gaps can be filled with unnamed bit fields, or you can use an unnamed field of width `0` to force alignment with the next integer boundary:

```text
struct stuff 
{
    unsigned int field1: 30;
    unsigned int       : 2;
    unsigned int field2: 4;
    unsigned int       : 0;   // align next field to next unsigned int boundary
    unsigned int field3: 3; 
};
```

Now there is a 2‑bit gap between `field1` and `field2`, and `field3` resides in the next `unsigned int` unit, giving this struct a total size of `3 * 32 = 96` bits.

Code to study: [bit.cpp](bit.cpp)


## Initialization and bit‑field remapping


### Initialization


Bit fields are initialized just like ordinary structs. Two common forms are:

```text
struct stuff s1 = {20, 8, 6};
```

or by assigning members one by one:

```text
struct stuff s1;
s1.field1 = 20;
s1.field2 = 8;
s1.field3 = 4;
```


### Bit‑field remapping


Define a 32‑bit wide bit‑field struct:

```text
struct box {
    unsigned int ready:     2;
    unsigned int error:     2;
    unsigned int command:   4;
    unsigned int sector_no: 24;
} b1;
```


#### Using pointer cast to zero the bit‑field


```text
int *p = (int *) &b1;    // map the address of the bit‑field struct to an int* address
*p = 0;                  // clear the entire struct, setting all bit‑field members to 0
```


#### Using a union to map the 32‑bit bit field to an `unsigned int`


First, a brief introduction to `union`:

> A **union** is a special kind of class and a derived data type. Inside a union you can declare multiple different data types, and a variable of that union type may hold any one of them at a time, all sharing the same memory region to save space.
> 
> A union is similar to a struct in syntax, but fundamentally different: in a struct each member has its own memory space and the total size is the sum of all members (ignoring padding). In a union all members share the same memory block, and the size of the union is the size of its largest member. Note that “sharing” here does not mean all members can be stored simultaneously; rather, the union can be assigned any one member value at a time, and assigning a new value overwrites the previous one.


You can declare a union such as:

```text
union u_box {
    struct box   st_box;
    unsigned int ui_box;
};
```

On x86, both `unsigned int` and `box` occupy 32 bits, so `st_box` and `ui_box` share the same memory block. The exact correspondence between bit‑field bits and `unsigned int` bits depends on the compiler and hardware. To zero the entire bit field via the union, write:

```text
union u_box u;
u.ui_box = 0;
```

> Reference: <https://en.cppreference.com/w/cpp/language/bit_field.html>