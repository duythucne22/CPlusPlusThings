- [Stories About C++](#stories-about-c)
    - [Major Projects](#major-projects)
    - [About the Author](#about-the-author)
    - [Running the Project](#running-the-project)
      - [Method 1: vscode + bazel](#method-1-vscode--bazel)
      - [Method 2: docker](#method-2-docker)
      - [Method 3: g++](#method-3-g)
    - [Video‑based Learning](#videobased-learning)
    - [Lark Knowledge Base](#lark-knowledge-base)
    - [Basics and Beyond](#basics-and-beyond)
    - [Hands‑on Series](#handson-series)
      - [10‑Day Intensive Practice](#10day-intensive-practice)
      - [Key Hands‑on Exercises](#key-handson-exercises)
    - [C++2.0 New Features](#c20-new-features)
      - [Overview](#overview)
      - [C++11 New Features](#c11-new-features)
      - [C++14/17/20](#c141720)
    - [Design Patterns](#design-patterns)
    - [STL Source Code Analysis](#stl-source-code-analysis)
    - [Concurrency Programming](#concurrency-programming)
      - [C++ Concurrency in Action](#c-concurrency-in-action)
      - [Multithreading and Multiprocessing](#multithreading-and-multiprocessing)
        - [Threading In C++](#threading-in-c)
    - [C++ Idioms](#c-idioms)
        - [What are your favorite C++ programming style idioms?](#what-are-your-favorite-c-programming-style-idioms)
    - [Learning Courses](#learning-courses)
      - [Geek Time: 30 Practical Lectures on Modern C++](#geek-time-30-practical-lectures-on-modern-c)
    - [Tools](#tools)
      - [Container Quick Output Utility](#container-quick-output-utility)
      - [Simple Python‑style Output (Jupyter Notebook)](#simple-pythonstyle-output-jupyter-notebook)
      - [Inspecting Compilation‑Process Changes](#inspecting-compilationprocess-changes)
      - [C++ Debug Macro: dbg‑macro](#c-debug-macro-dbgmacro)
      - [Debug Tool rr on Linux – “Time‑Travel” Capability](#debug-tool-rr-on-linux--timetravel-capability)
    - [Extensions](#extensions)
      - [Some Common Questions](#some-common-questions)
    - [Contributors](#contributors)


# Stories About C++

Thanks for your support of *Stories About C++*! We’ve now synchronized the content to Bilibili as video episodes, so you can also learn by watching while still reading this online. Please feel free to star, share, and submit PRs.

Online personal blog: [Guangcheng’s Lab](https://light-city.github.io/)

Online learning site: [Stories About C++](https://light-city.github.io/stories_things/)

- Chinese name: **C++ 那些事**
- English name: **Stories About C Plus Plus**

This is a repository suitable for beginners going from **getting started to advanced**, solving the problems that **interviewees and learners** have about how to **dive into C++** and how to **fall in love with C++**. In addition, the repository extends into deeper topics such as source‑code analysis and multithreaded concurrency, making it a fairly comprehensive C++ learning repository that carries you from beginner to advanced level.

### Major Projects

A series of major projects have been launched to help everyone learn C++ through hands‑on practice. Combined with this open‑source project, progress can be very rapid.


Entry point: [Click here](./proj/README.md)


### About the Author


The official WeChat account now has two main sections: “Albums” and “Menu”, where you can directly read the *Stories About C++* content inside WeChat. Combined with the code in this repository, the experience is extremely enjoyable, so we recommend you follow it.

WeChat official account: guangcity

Or scan the QR code below. Feedback and C++‑related discussions are welcome. I’ve created a “Stories About C++” discussion group on WeChat; after following the official account above, click the “Contact Me” button in the bottom‑right corner of the account page to get invited into the group.


---

> Follow me


If you like it, follow me~


<table>
  <tbody>
    <tr>
      <th align="center" style="height=200 width="200">
          <img src="./img/cpp.jpg" height="200" width="200" ><br>
          Membership community
      </th>
      <th align="center" style="height=200 width="200">
          <img src="./img/wechat.jpg" height="200" width="200" ><br>
          WeChat official account
      </th>
    </tr>
  </tbody>
</table>



### Running the Project

#### Method 1: vscode + bazel

#### Method 2: docker

A no‑dev‑environment Docker image has been introduced. You can pull the image below:


```
docker pull xingfranics/cplusplusthings:latest
```

#### Method 3: g++

### Video‑based Learning

[Episode 1: Step‑by‑Step Compilation of This Project](https://www.bilibili.com/video/BV1Rv4y1H7LB/?vd_source=bb6532dcd5b1d6b26125da900adb618e)


[Episode 2: No‑dev‑environment Docker Setup](https://www.bilibili.com/video/BV1oz4y1a7Pu/?vd_source=bb6532dcd5b1d6b26125da900adb618e)


[Episode 3: Line‑by‑line Reading of HashTable – Deep Dive into C++ STL](https://www.bilibili.com/video/BV1o8411U7vy/?vd_source=bb6532dcd5b1d6b26125da900adb618e)


[Episode 4: Line‑by‑Line Reading of STL’s enable_shared_from_this](https://www.bilibili.com/video/BV1du4y1w7Mg/?spm_id_from=333.788&vd_source=bb6532dcd5b1d6b26125da900adb618e)


[Episode 5: Line‑by‑Line Reading of STL Threading – from C++11 thread to C++20 jthread](https://www.bilibili.com/video/BV1DH4y1g7gS/?vd_source=bb6532dcd5b1d6b26125da900adb618e)


[Episode 6: Line‑by‑Line Reading of STL condition_variable and condition_variable_any](https://www.bilibili.com/video/BV13b421b7Am/?spm_id_from=333.999.0.0&vd_source=bb6532dcd5b1d6b26125da900adb618e)


[Episode 7: Line‑by‑Line Reading of STL Mutex](https://www.bilibili.com/video/BV1xm42157pq/?spm_id_from=333.999.0.0&vd_source=bb6532dcd5b1d6b26125da900adb618e)


[Episode 8: Line‑by‑Line Reading of STL RAII Lock](https://www.bilibili.com/video/BV1Ls421g7iq/?spm_id_from=333.788&vd_source=bb6532dcd5b1d6b26125da900adb618e)


### Lark Knowledge Base

[Real Interview Records from Internet Giants](https://hmpy6adnp5.feishu.cn/docx/OitBdRB4KozIhTxQt7Ec7iFDnkc)


[Must‑read Interview Guide for Landing Offers](https://hmpy6adnp5.feishu.cn/docx/B1aCdVTUgoyJGYxtWV7cdvgRnxv)


### Basics and Beyond

- [`const` Tips and Tricks](./basic_content/const)
- [`static` Tips and Tricks](./basic_content/static)
- [`this` Tips and Tricks](./basic_content/this)
- [`inline` Tips and Tricks](./basic_content/inline)
- [`sizeof` Tips and Tricks](./basic_content/sizeof)
- [Function Pointers Tips and Tricks](./basic_content/func_pointer)
- [Pure Virtual Functions and Abstract Classes Tips and Tricks](./basic_content/abstract)
- [`vptr_vtable` Tips and Tricks](./basic_content/vptr_vtable)
- [`virtual` Tips and Tricks](./basic_content/virtual)
- [`volatile` Tips and Tricks](./basic_content/volatile)
- [`assert` Tips and Tricks](./basic_content/assert)
- [Bit Fields Tips and Tricks](./basic_content/bit)
- [`extern` Tips and Tricks](./basic_content/extern)
- [`struct` Tips and Tricks](./basic_content/struct)
- [`struct` vs `class` Tips and Tricks](./basic_content/struct_class)
- [`union` Tips and Tricks](./basic_content/union)
- [Implementing C++ Polymorphism in C Tips and Tricks](./basic_content/c_poly)
- [`explicit` Tips and Tricks](./basic_content/explicit)
- [`friend` Tips and Tricks](./basic_content/friend)
- [`using` Tips and Tricks](./basic_content/using)
- [`::` Tips and Tricks](./basic_content/maohao)
- [`enum` Tips and Tricks](./basic_content/enum)
- [`decltype` Tips and Tricks](./basic_content/decltype)
- [References and Pointers Tips and Tricks](./basic_content/pointer_refer)
- [Macros Tips and Tricks](./basic_content/macro)


### Hands‑on Series

#### [10‑Day Intensive Practice](./practical_exercises/10_day_practice)


- [Day 1 – Basic Syntax](practical_exercises/10_day_practice/day1)


- [Day 2 – Recursion, Structs, Enums, Static Variables, etc.](practical_exercises/10_day_practice/day2)


- [Day 3 – Functions 1](practical_exercises/10_day_practice/day3)


- [Day 4 – Functions 2](practical_exercises/10_day_practice/day4)


- [Day 5 – Inheritance and Polymorphism](practical_exercises/10_day_practice/day5)


- [Day 6 – Virtual Functions and Abstract Classes](practical_exercises/10_day_practice/day6)


- [Day 7 – Operator Overloading](practical_exercises/10_day_practice/day7)


- [Day 8 – Templates and STL](practical_exercises/10_day_practice/day8)


- [Day 9 – Exceptions](practical_exercises/10_day_practice/day9)


- [Day 10 – Files and Streams](practical_exercises/10_day_practice/day10)


#### [Key Hands‑on Exercises](./practical_exercises/key_exercises/)


- [Overloading Square Brackets.cpp](./practical_exercises/key_exercises/bracket_overloading.cpp)


- [Clock ++ Operator Overloading.cpp](./practical_exercises/key_exercises/clock.cpp)


- [Type‑Cast Operator Overloading.cpp](./practical_exercises/key_exercises/operator_cast.cpp)


- [Circle‑Parentheses Overloading for Clock.cpp](./practical_exercises/key_exercises/operator_circle.cpp)


- [Function Template.cpp](./practical_exercises/key_exercises/func_temp.cpp)


- [Dynamic Array.cpp](./practical_exercises/key_exercises/array.cpp)


- [Dictionary Insert and Lookup.cpp](./practical_exercises/key_exercises/map_insert_look.cpp)


- [Exception Handling Try.cpp](./practical_exercises/key_exercises/try.cpp)


- [Class Template Stack.cpp](./practical_exercises/key_exercises/stack.cpp)


- [Class Template Specialization for Array.cpp](./practical_exercises/key_exercises/array_template.cpp)


- [Inheritance and Encapsulation.cpp](./practical_exercises/key_exercises/override.cpp)


- [Comprehensive File Read/Write Problem.cpp](./practical_exercises/key_exercises/read_file.cpp)


- [Input/Output Operator Overloading.cpp](./practical_exercises/key_exercises/io_operator_overload.cpp)


- [Input/Output Overloading.cpp](./practical_exercises/key_exercises/io_operator.cpp)


- [Output Formatting.cpp](./practical_exercises/key_exercises/output.cpp)



### [C++2.0 New Features](./cpp2.0)


#### Overview


C++2.0 is a shorthand term meaning “Modern C++”, covering C++11/14/17/20.


#### [C++11 New Features](./cpp2.0/cpp11)


- [Variadic Templates](./cpp2.0/cpp11/variadic)


- Spaces in Template Expressions


  ```cpp
  vector<list<int> > // ok in each C++ version
  vector<list<int>>  // before C++11: error: ‘>>’ should be ‘> >’ within a nested template argument list; accepted in C++11 and later
  ```


- [nullptr and nullptr_t](./cpp2.0/cpp11/nullptr.cpp)


- [Automatic Type Deduction with auto](./cpp2.0/cpp11/auto.cpp)


- [Uniform Initialization](./cpp2.0/cpp11/uniform_initialization.cpp)


- [initializer_list](./cpp2.0/cpp11/initializer.cpp)


- [explicit for ctors taking more than one argument](./cpp2.0/cpp11/explicit.cpp)


- [Range‑based for statements](./cpp2.0/cpp11/auto.cpp)


  ```cpp
  for(decl:col) {
      statement
  }
  ```


- [=default, =delete](./cpp2.0/cpp11/default_delete.cpp)


  If you define a constructor yourself, the compiler won’t automatically generate a default constructor.  
  By explicitly adding `=default`, you can regain and use the default constructor again.


- Alias (type‑alias) Templates (template typedef)


  - [alias.cpp](./cpp2.0/cpp11/alias.cpp)
  - [template_template.cpp](./cpp2.0/cpp11/template_template.cpp)


- [Template Template Parameters](./cpp2.0/template_template.cpp)


- [Type Aliases](./cpp2.0/cpp11/type_alias.cpp)


- [noexcept](./cpp2.0/cpp11/noexcept.cpp)


- [override](./cpp2.0/cpp11/override.cpp)


- [final](./cpp2.0/cpp11/final.cpp)


- [decltype](./cpp2.0/cpp11/decltype.cpp)


- [lambda](./cpp2.0/cpp11/lambda.cpp)


- [Rvalue References](./cpp2.0/cpp11/rvalue.cpp)


- [Move‑Aware Classes](./cpp2.0/cpp11/move.cpp)


- Containers – Structure and Classification


  - (1) Sequence containers: `array` (new in C++2.0), `vector`, `deque`, `list`, `forward_list` (new in C++2.0)
  - (2) Associative containers: `set/multiset`, `map/multimap`
  - (3) Unordered containers (new in C++2.0; replacing `hash_xxx` with `unordered_xxx`): `unordered_map/unordered_multimap`, `unordered_set/unordered_multiset`


- [Hash Function](./cpp2.0/cpp11/hash.cpp)


- [tuple](./cpp2.0/cpp11/tuple.cpp)


  Learning resource: https://www.bilibili.com/video/av51863195?from=search&seid=3610634846288253061


#### C++14/17/20


To be updated…


### Design Patterns


- [Singleton Pattern](./design_pattern/singleton)
- [Producer–Consumer Pattern](./design_pattern/producer_consumer)


### [STL Source Code Analysis](./src_analysis/stl)


**STL Source Code Analysis: gcc 4.9.1**


- [array](./src_analysis/stl/array.md)
- [deque](./src_analysis/stl/deque.md)
- [queue and stack](./src_analysis/stl/queue_stack.md)
- [list](./src_analysis/stl/list.md)
- [vector](./src_analysis/stl/vector.md)
- [typename](./src_analysis/stl/typename.md)
- [traits](./src_analysis/stl/traits.md)
- [iterator](./src_analysis/stl/iterator.md)
- [On STL Design – EBO Optimization](./src_analysis/stl/谈谈STL设计之EBO优化.md)
- [rb_tree](./src_analysis/stl/rb_tree.md)
- [set and multiset](./src_analysis/stl/set_multiset.md)
- [map and multimap](./src_analysis/stl/map_multimap.md)
- [hashtable](./src_analysis/stl/hashtable.md)
- [myhashtable](./src_analysis/stl/myhashtable.md)
- [unordered_map](./src_analysis/stl/unordered_map.md)


### [Concurrency Programming](./concurrency)


#### C++ Concurrency in Action


- [Chapter 1](./concurrency/concurrency_v1/chapter1)
- [Chapter 2](./concurrency/concurrency_v1/chapter2)


Learning resource: https://downdemo.gitbook.io/cpp-concurrency-in-action-2ed/


#### Multithreading and Multiprocessing


##### Threading In C++


- [Introduction](./concurrency/Threading_In_CPlusPlus/1.thread)
- [Five Ways to Create Threads](./concurrency/Threading_In_CPlusPlus/2.create_type)
- [Join and Detach](./concurrency/Threading_In_CPlusPlus/3.join_detach)
- [Mutex in C++ Threading](./concurrency/Threading_In_CPlusPlus/4.mutex)


> Studied from:
>
> [https://www.youtube.com/watch?v=eZ8yKZo-PGw&list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp&index=4](https://www.youtube.com/watch?v=eZ8yKZo-PGw&list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp&index=4)


### [C++ Idioms](./codingStyleIdioms)


##### What are your favorite C++ programming style idioms?


- [1. Class initializer lists](./codingStyleIdioms/1_classInitializers)
- [2. Using enum class instead of namespaces](./codingStyleIdioms/2_enumclass_namespace)
- [3. RAII (Resource Acquisition Is Initialization)](./codingStyleIdioms/3_RAII)
- [4. Copy and swap](./codingStyleIdioms/4_copy-swap)
- [5. pImpl (Pointer to Implementation)](./codingStyleIdioms/5_pImpl)


### Learning Courses


#### [Geek Time: 30 Practical Lectures on Modern C++](https://time.geekbang.org/channel/home)


- [Heaps, stacks, RAII: How should resources be managed in C++?](./learn_class/modern_cpp_30/RAII)
  - [Heap](./learn_class/modern_cpp_30/RAII/heap.cpp)
  - [Stack](./learn_class/modern_cpp_30/RAII/stack.cpp)
  - [RAII](./learn_class/modern_cpp_30/RAII/RAII.cpp)
- [Implementing smart pointers in C++ by yourself](./learn_class/modern_cpp_30/smart_ptr)
  - [auto_ptr, scoped_ptr](./learn_class/modern_cpp_30/smart_ptr/auto_scope.cpp)
  - [unique_ptr](./learn_class/modern_cpp_30/smart_ptr/unique_ptr.cpp)
  - [shared_ptr](./learn_class/modern_cpp_30/smart_ptr/shared_ptr.cpp)
- [What problems do rvalues and move operations solve?](./learn_class/modern_cpp_30/reference)
  - [Lvalues and rvalues](./learn_class/modern_cpp_30/reference/reference.cpp)
  - [Extending lifetimes](./learn_class/modern_cpp_30/reference/lifetime.cpp)
  - [Reference collapsing](./learn_class/modern_cpp_30/reference/collapses.cpp)
  - [Perfect forwarding](./learn_class/modern_cpp_30/reference/forward.cpp)
  - [Never return references to local variables](./learn_class/modern_cpp_30/reference/don'treturnReference.cpp)
- [Containers 1](./learn_class/modern_cpp_30/container1)
- [Containers 2](./learn_class/modern_cpp_30/container2)
- [Exceptions](./learn_class/modern_cpp_30/exception)
- [Literals, static assertions, and member function specifiers](./learn_class/modern_cpp_30/literalAssert)
- [Should you return objects or references?](./learn_class/modern_cpp_30/returnObj)
- [Compile‑time polymorphism: generic programming and template basics](./learn_class/modern_cpp_30/compilerpoly)
- [What can be done at compile‑time? A full computational world](./learn_class/modern_cpp_30/compilercompute)
- [SFINAE: What does “substitution failure is not an error” really mean?](./learn_class/modern_cpp_30/SFINAE)
- [constexpr: A world of compile‑time constants](./learn_class/modern_cpp_30/constexpr)
- [Function objects and lambdas: stepping into functional programming](./learn_class/modern_cpp_30/functionLambda)
- [Memory models and atomic: understanding the complexity of concurrency](./learn_class/modern_cpp_30/memorymodel_atomic)


### Tools


#### [Container Quick Output Utility](./tool/output)


Modified from the original code by Professor Wu. [Click here to jump to the code](./tool/output/output_container.h)


Input example:


```cpp
map<int, int> mp{
            {1, 1},
            {2, 4},
            {3, 9}};
    cout << mp << endl;
```


Output result:


```cpp
{ 1 => 1, 2 => 4, 3 => 9 }
```


#### Simple Python‑style Output (Jupyter Notebook)


- [Playing with C/C++ like in Python](./tool/像Python一样玩CC++.md)


#### Inspecting Compilation‑Process Changes


- [https://cppinsights.io](https://cppinsights.io)


#### C++ Debug Macro: dbg‑macro

- [C++ Debug Tool: dbg‑macro](./tool/C++的Debug工具dbg-macro.md)

#### Debug Tool rr on Linux – “Time‑Travel” Capability

- [Using rr for debugging](./tool/用rr来进行debug.md)

### Extensions

#### Some Common Questions

- [How to convert a string to an int in C++?](./extension/some_problem/string_int.md)


### Contributors

| Contributor | URL                          |
|-----------|------------------------------|
| Guangcheng  | [https://github.com/Light-City](https://github.com/Light-City) |
| ChungZH   | [https://github.com/ChungZH](https://github.com/ChungZH)    |
| xliu79    | [https://github.com/xliu79](https://github.com/xliu79)     |
