# Compile‑Time Polymorphism: Introduction to Generic Programming and Templates


Runtime polymorphism is achieved through interfaces or virtual functions. This section focuses on **compile‑time polymorphism** instead.


> If a bird walks like a duck, swims like a duck, and quacks like a duck, then it can be treated as a duck.

**Duck typing** lets developers implement flexible “contracts” without relying on inheritance hierarchies, and it makes it possible to combine code from different sources, even when the objects come from different inheritance trees. The only requirement is that these objects have common member functions. These functions must share the **same name** and **structurally similar parameters** (their parameter types do not need to be identical).

In C++, duck typing is implemented via **templates**, that is, **generic programming**. For both class templates and function templates, the compiler can only perform basic syntactic checks when it sees the template definition. Real type checking happens only at **instantiation time**, which is when template‑related errors are usually reported.


> **“Dynamic” polymorphism vs “Static” polymorphism**

**Dynamic polymorphism** deals with behavior that changes at runtime—something that cannot be determined at compile time. In contrast, **static polymorphism** (or **generic programming**) addresses a different problem: it lets you write a single algorithm that works uniformly over many different types, emphasizing **code reuse** instead of runtime dispatch.
