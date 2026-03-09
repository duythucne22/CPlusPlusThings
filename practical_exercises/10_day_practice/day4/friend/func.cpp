// Use friend function to calculate distance between two points
#include <cmath>
#include <iostream>
using namespace std;
class Point {
public:
  Point(int x = 0, int y = 0) : X(x), Y(y) {}
  int GetX() { return X; }
  int GetY() { return Y; }
  friend float Distance(Point &a, Point &b);

private:
  int X, Y; // Private data members
};
// By declaring one module as a friend of another, a module can access information that is otherwise hidden in another module.
float Distance(Point &a, Point &b) {
  double dx = a.X - b.X;
  double dy = a.Y - b.Y;
  return sqrt(dx * dx + dy * dy);
}

int main() {
  Point p1(3.0, 5.0), p2(4.0, 6.0);
  cout << "Distance between two points: " << Distance(p1, p2) << endl;
  
  return 0;
}

