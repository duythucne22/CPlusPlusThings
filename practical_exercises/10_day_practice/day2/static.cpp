/* Static Variable.cpp */
#include <iostream>
using namespace std;
int i = 1; // i is a global variable with static storage duration.
int main(void) {
  static int a; // Static local variable, has global lifetime, locally visible.
  int b = -10;  // b, c are local variables with dynamic storage duration.
  int c = 0;
  void other(void);
  cout << "---MAIN---\n";
  cout << " i: " << i << " a: " << a << " b: " << b << " c: " << c
       << endl; // 1 0 -10 0
  c = c + 8;
  other(); // 33 4 0 15
  cout << "---MAIN---\n";
  cout << " i: " << i << " a: " << a << " b: " << b << " c: " << c
       << endl; // 33 0 -10 8
  i = i + 10;
  other(); // 75 6 4 15
  other(); // 107 8 6 15
  
  return 0;
}
void other(void) {
  static int a = 2;
  static int b;
  // a,b are static local variables with global lifetime, locally visible.
  // Initialized only the first time entering the function.
  int c = 10; // c is a local variable with dynamic storage duration
  // Initialized every time entering the function.
  a = a + 2;
  i = i + 32;
  c = c + 5;
  cout << "---OTHER---\n";
  cout << " i: " << i << " a: " << a << " b: " << b << " c: " << c << endl;
  b = a;
}

