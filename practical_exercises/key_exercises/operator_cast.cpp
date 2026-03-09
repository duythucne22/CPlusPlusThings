/* Operator Overloading - Type Conversion.cpp */
/*
There is a class Circle, design type conversion functions for this class:
- When converting Circle object to int, return the circle's radius;
- When converting to double, return the circle's circumference;
- When converting to float, return the circle's area.
*/

/*

Type conversion functions have no parameters.
Type conversion functions have no return type.
Type conversion functions must return data of the type being converted to.

*/

#include <iostream>
using namespace std;
class Circle {
private:
  double x, y, r;

public:
  Circle(double x1, double y1, double r1) {
    x = x1;
    y = y1;
    r = r1;
  }
  operator int() { return int(r); }
  operator double() { return 2 * 3.14 * r; }
  operator float() { return (float)3.14 * r * r; }
};
int main() {
  Circle c(2.3, 3.4, 2.5);
  int r = c;         // Call operator int(), convert Circle to int
  double length = c; // Call operator double(), convert to double
  float area = c;    // Call operator float(), convert Circle to float
  double len = (double)c; // Force convert Circle type object to double
  cout << r << endl;
  cout << length << endl;
  cout << len << endl;
  cout << area << endl;
  
}
