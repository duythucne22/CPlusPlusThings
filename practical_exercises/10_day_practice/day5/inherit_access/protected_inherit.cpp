/*
Protected inheritance is when the inheritance mode is protected.
In this inheritance mode, the base class's public members become protected members in the derived class.
The base class's protected and private members maintain their original access权限 in the derived class.
*/
#include <iostream>
using namespace std;
class Base {
  int x;

protected:
  int getx() { return x; }

public:
  void setx(int n) { x = n; }
  void showx() { cout << x << endl; }
};
class Derived : protected Base {
  int y;

public:
  void sety(int n) { y = n; }
  void sety() { y = getx(); } // Access base class's protected member
  void showy() { cout << y << endl; }
};
int main() {
  Derived obj;
  obj.setx(10); // Error
  obj.sety(20);
  obj.showx(); // Error
  obj.showy();
  
}

/*
Explanation:
As shown in the text above, protected inheritance changes base class's public to protected.
For protected members, when used externally, an error will occur.
So setx and showx access errors. However, for derived classes, they can directly access base class's protected members.
In derived class, y=getx() can be accessed normally!
*/

