/* Abstract Class.cpp */
#include <iostream>
using namespace std;
class Figure {
protected:
  double x, y;

public:
  void set(double i, double j) {
    x = i;
    y = j;
  }
  virtual void area() = 0;
};

class Trianle : public Figure {
public:
  void area() { cout << "Triangle area: " << x * y * 0.5 << endl; }
};
class Rectangle : public Figure {
public:
  void area() { cout << "This is a rectangle, its area is: " << x * y << endl; }
};

int main(int argc, char const *argv[]) {
  // Define abstract class pointer
  Figure *pF = NULL;
  // Figure f1; Abstract class cannot be instantiated
  Rectangle r;
  Trianle t;
  t.set(10, 20);
  pF = &t;
  pF->area();
  r.set(10, 20);
  pF = &r;
  pF->area();
  // Define abstract class reference
  Figure &rF = t;
  rF.set(20, 20);
  rF.area();
  
  return 0;
}
