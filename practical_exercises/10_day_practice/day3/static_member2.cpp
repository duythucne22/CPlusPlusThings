/* Static Member Function 2.cpp */
#include <iostream>
using namespace std;
class A {
public:
  static void f(A a);

private:
  int x;
};
void A::f(A a) {

  // Static member functions can only access static data members or static member functions of the class.
  // cout<<x; // Referencing x is wrong
  cout << a.x; // Correct
}

int main(int argc, char const *argv[]) {
  A a;
  a.f(A());
  
  return 0;
}

