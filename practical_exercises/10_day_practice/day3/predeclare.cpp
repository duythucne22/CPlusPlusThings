/* Class Forward Declaration.cpp */
/*
Although using forward reference declarations can solve some problems, it is not a panacea.
It should be noted that although a forward reference declaration is used, before providing a complete class declaration,
you cannot declare objects of that class, nor can you use objects of that class in inline member functions.
Please see the following code:
*/

// First method
#include <iostream>
class Fred; // Forward reference declaration
class Barney {
  Fred x; // Error: Class Fred's declaration is not yet complete
};
class Fred {
  Barney y;
};

// Second method
class Fred; // Forward reference declaration

class Barney {
public:
  void method() {
    x->yabbaDabbaDo(); // Error: Fred class object used before definition
  }

private:
  Fred *x; // Correct, after forward reference declaration, you can declare pointer to Fred class
};

class Fred {
public:
  void yabbaDabbaDo();

private:
  Barney *y;
};

/*
Summary: When using forward reference declarations, you can only use the declared symbols,
and cannot involve any details of the class.
*/

