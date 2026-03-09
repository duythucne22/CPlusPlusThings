#include <iostream>
using namespace std;
class R {
public:
  R(int r1, int r2) {
    R1 = r1;
    R2 = r2;
  }
  // const distinguishes overloaded member functions
  void print();
  void print() const;

private:
  int R1, R2;
};
/*
Format for const member function declaration: type_specifier function_name(parameter_list) const;
Here, const is part of the function type, so the implementation must also include the const keyword.
The const keyword can be used to distinguish overloaded functions.
Const objects can only call their const member functions.
*/

void R::print() {
  cout << "Normal call" << endl;
  cout << R1 << ":" << R2 << endl;
}
// Instantiation also needs to include const
void R::print() const {
  cout << "Const object call" << endl;
  cout << R1 << ";" << R2 << endl;
}
int main() {
  R a(5, 4);
  a.print(); // Call void print()
  // Const objects can only call their const member functions
  const R b(20, 52);
  b.print(); // Call void print() const
  
  return 0;
}


#include <iostream>
using namespace std;
void display(const double &r);

class A {
public:
  A(int i, int j) {
    x = i;
    y = j;
  }

private:
  int x, y;
};
int main() {
  double d(9.5);
  display(d);
  A const a(3, 4); // a is a const object, cannot be modified
  
  return 0;
}
void display(const double &r)
// Const reference as parameter, cannot modify the object it refers to in the function.
{
  cout << r << endl;
}

