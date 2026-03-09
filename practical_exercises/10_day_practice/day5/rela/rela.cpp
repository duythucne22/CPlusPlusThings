/* Base Class and Derived Class (Important).cpp */
#include <iostream>
using namespace std;
class A {
  int a;

public:
  void setA(int x) { a = x; }
  int getA() { return a; }
};
class B : public A {
  int b;

public:
  void setB(int x) { b = x; }
  int getB() { return b; }
};
void f1(A a, int x) { a.setA(x); }
void f2(A *pA, int x) { pA->setA(x); }
void f3(A &rA, int x) { rA.setA(x); }

int main() {
  A a1, *pA;
  B b1;
  a1.setA(1);
  b1.setA(2);
  // Assign derived class object to base class object.
  a1 = b1;
  cout << a1.getA() << endl;
  cout << b1.getA() << endl;
  a1.setA(10);
  cout << a1.getA() << endl;
  cout << b1.getA() << endl;
  // Assign derived class object's address to base class pointer.
  pA = &b1;
  pA->setA(20);
  cout << pA->getA() << endl;
  cout << b1.getA() << endl;
  // Use derived class object to initialize reference to base class object.
  A &ra = b1;
  ra.setA(30);
  cout << pA->getA() << endl;
  cout << b1.getA() << endl;
  b1.setA(7);
  cout << b1.getA() << endl;
  f1(b1, 100);
  cout << "1111111111" << endl;
  cout << b1.getA() << endl; // 7
  f2(&b1, 200);
  cout << b1.getA() << endl;
  f3(b1, 300);
  cout << b1.getA() << endl;
  
  return 0;
}

