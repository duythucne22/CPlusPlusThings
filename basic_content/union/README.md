# Stories About `UNION`


## About the Author


Personal WeChat official account:


![](../img/wechat.jpg)


A **union** is a special kind of space‑saving class that can have multiple data members, but at any given time only one member can hold a valid value. Once a member is assigned, other members become undefined. Unions have the following characteristics:

- The default access specifier is `public`.  
- They can have constructors and destructors.  
- They cannot contain members of reference type.  
- They cannot inherit from other classes and cannot be used as a base class.  
- They cannot contain virtual functions.  
- An **anonymous union** can expose its members directly in the enclosing scope.  
- An anonymous union cannot contain `protected` or `private` members.  
- A global anonymous union must be declared `static`.  
