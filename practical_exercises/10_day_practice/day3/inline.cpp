/* Inline Function.cpp */
#include <iostream>
using namespace std;
// Function declaration
inline double CalArea(double radius);
int main(int argc, char const *argv[]) {
  double r(3.0);
  double area;
  area = CalArea(r);
  cout << area << endl;
  
  return 0;
}
// Add keyword inline
inline double CalArea(double radius) { return 3.14 * radius * radius; }

