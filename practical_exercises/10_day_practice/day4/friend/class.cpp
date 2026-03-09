#include <iostream>
using namespace std;
/*
If one class is a friend of another class, all members of this class can access the private members of the other class.
Declaration syntax: Use friend modifier before the friend class name when declaring in another class.
*/

/*
If class B is declared as a friend of class A, B's member functions can access A's private and protected data,
but A's member functions cannot access B's private and protected data.
*/
class A {
  friend class B;

public:
  void Display() { cout << x << endl; }

private:
  int x;
};
class B {
public:
  void Set(int i);
  void Display();

private:
  A a;
};
void B::Set(int i) { a.x = i; }
void B::Display() { a.Display(); }

int main(int argc, char const *argv[]) {
  B b;
  b.Set(10);
  b.Display();

  
  return 0;
}

/*
If class B is declared as a friend of class A, B's member functions can access A's private and protected data,
but A's member functions cannot access B's private and protected data
*/

