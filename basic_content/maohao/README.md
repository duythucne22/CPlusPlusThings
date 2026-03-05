# Stories About the `::` Scope Resolution Operator


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


- **Global scope operator (`::name`)**:  
  Precedes names of types (classes, class members, member functions, variables, etc.) to indicate that the name belongs to the **global namespace**.

- **Class scope operator (`class::name`)**:  
  Used to specify that the name is within the scope of a particular class, e.g., `MyClass::myStaticMember` or `MyClass::myMethod`.

- **Namespace scope operator (`namespace::name`)**:  
  Used to indicate that the name belongs to a specific namespace, e.g., `std::cout` or `MyNamespace::MyType`.

Example code: [maohao.cpp](maohao.cpp)