/* Exception Handling.cpp */
#include <iostream>
using namespace std;
// Function exceptions can be thrown to be handled by the main function
void fun(int x) {
  try {
    if (x == 0)
      throw "exception";
  } catch (...) {
    cout << "in fun" << endl;
    throw 1;
  }
}

int main(int argc, char const *argv[]) {

  try {
    fun(0);
  } catch (int n) {
    cout << "in main" << endl;
  }

  
  return 0;
}
