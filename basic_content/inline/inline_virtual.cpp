#include <iostream>
using namespace std;

class Base {
public:
  inline virtual void who() { cout << "I am Base\n"; }
  virtual ~Base() {}
};

class Derived : public Base {
public:
  inline void who() // If "inline" is omitted, it is implicitly inline
  {
    cout << "I am Derived\n";
  }
};

int main() {
  // In this case, the virtual function who() is called
  // through a concrete object (b) of class Base, so the target
  // is known at compile time; the call can be inlined, though
  // actual inlining is still up to the compiler.
  Base b;
  b.who();


  // Here, the virtual function is called through a pointer,
  // so the actual function to call is resolved at runtime
  // (polymorphism), and thus it generally cannot be inlined.
  Base *ptr = new Derived();
  ptr->who();


  // Because Base has a virtual destructor (virtual ~Base() {}),
  // deleting through the base pointer will first call Derived's
  // destructor, then Base's destructor, preventing memory leaks.
  delete ptr;

  return 0;
}