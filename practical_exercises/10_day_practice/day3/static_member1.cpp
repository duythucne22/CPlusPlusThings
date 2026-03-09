/* Static Member Function 1.cpp */
/*
Knowledge points:
Static member function
Class code can call static member functions using the class name and scope resolution operator.
Static member functions can only access static data members or static member functions of the class.
*/
#include <iostream>
using namespace std;
class Application {
public:
  static void f();
  static void g();

private:
  static int global;
};
int Application::global = 0;
void Application::f() { global = 5; }
void Application::g() { cout << global << endl; }

int main() {
  Application::f();
  Application::g();
  
  return 0;
}

