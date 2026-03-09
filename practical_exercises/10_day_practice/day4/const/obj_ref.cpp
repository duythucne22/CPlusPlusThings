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
  A const a(3, 4); // a is a const object, cannot be updated
  
  return 0;
}
void display(const double &r)
// Const reference as parameter, cannot update the object r refers to in the function.
{
  cout << r << endl;
}

