
#include <iostream>
using namespace std;
class Base {
  int x;

public:
  void setx(int n) { x = n; }
  int getx() { return x; }
  void showx() { cout << x << endl; }
};
// Private inheritance
// Base class's public members become private in derived class, private members are inaccessible in derived class.
class derived : private Base {
  int y;

public:
  void sety(int n) { y = n; }
  void sety() { y = getx(); }
  void showy() { cout << y << endl; }
};
int main() {
  derived obj;
  obj.setx(10); // cannot access
  obj.sety(20);
  obj.showx(); // cannot access
  obj.showy();
}

