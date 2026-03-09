/* Derived Class Initialization.cpp */
#include <iostream>
using namespace std;
class A {
  int a;

public:
  A(int x) {
    a = x;
    cout << "Constructing Virtual Base A..." << endl;
  }
};
class B : virtual public A {
public:
  B(int i) : A(i) { cout << "Constructing Virtual Base B..." << endl; }
};
class C : virtual public A {
  int x;

public:
  C(int i) : A(i) {
    cout << "Constructing C..." << endl;
    x = i;
  }
};
class ABC : public C, public B {
public:
  // Virtual base class is initialized by the most derived class
  ABC(int i, int j, int k)
      : C(i), B(j), A(i) // L1, must initialize A here
  {
    cout << "Constructing ABC..." << endl;
  }
};
int main() {
  ABC obj(1, 2, 3);
  
  return 0;
}
