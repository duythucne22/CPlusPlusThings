/* Static Data Member.cpp */
/*
Learning:
Static data members
Declared with keyword static
All objects of this class maintain the same copy of this member
Must be defined and initialized outside the class, use (::) to specify which class it belongs to.
*/
#include <iostream>
using namespace std;
class Point {
public:
  Point(int xx = 0, int yy = 0) {
    X = xx;
    Y = yy;
    countP++;
  }
  Point(Point &p);
  int GetX() { return X; }
  int GetY() { return Y; }
  void GetC() { cout << " Object id=" << countP << endl; }

private:
  int X, Y;
  // Static data member, must be defined and initialized outside, cannot be initialized directly inside!
  static int countP;
};
Point::Point(Point &p) {
  X = p.X;
  Y = p.Y;
  countP++;
}
// Must be defined and initialized outside the class, use (::) to specify which class it belongs to.
int Point::countP = 0;
int main() {
  Point A(4, 5);
  cout << "Point A," << A.GetX() << "," << A.GetY();
  A.GetC();
  Point B(A);
  cout << "Point B," << B.GetX() << "," << B.GetY();
  B.GetC();
  
  return 0;
}

