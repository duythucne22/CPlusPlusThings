/* Union Learning.cpp */
#include <iostream>
using namespace std;
// Same memory address
union myun {
  struct {
    int x;
    int y;
    int z;
  } u;
  int k;
} a;
int main() {
  a.u.x = 4;
  a.u.y = 5;
  a.u.z = 6;
  a.k = 0; // Overwrite the first int space value
  printf("%d %d %d %d\n", a.u.x, a.u.y, a.u.z, a.k);
  
  return 0;
}

