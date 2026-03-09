#include <iostream>
using namespace std;
class base {
  int x;

public:
  void setx(int n) { x = n; }
  int getx() { return x; }
  void showx() { cout << x << endl; }
};
// Derived class
class derived : public base {
  int y;

public:
  void sety(int n) { y = n; }
  void sety() { y = getx(); }
  void showy() { cout << y << endl; }
};
// Derived class cannot directly access base class's private members, but can access them through base class's public member functions
int main() {
  derived obj;
  obj.setx(10);
  obj.sety(20);
  obj.showx();
  obj.showy();
  obj.sety();
  obj.showx();
  obj.showy();
  
}

