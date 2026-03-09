/*
Base class protected members:
Inside class: accessible
Class users: cannot access
Class derived class members: can access
*/
#include <iostream>
class B {
private:
  int i;

protected:
  int j;

public:
  int k;
};
class D : public B {
public:
  void f() {
    i = 1; // cannot access - derived class cannot access base class private members
    j = 2; // derived class can access base class protected members
    k = 3;
  }
};
int main() {
  B b;
  b.i = 1; // cannot access - private members, class users cannot access
  b.j = 2; // cannot access - protected members, class users cannot access
  b.k = 3;
  
  return 0;
}

