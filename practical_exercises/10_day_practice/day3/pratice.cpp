/* Comprehensive Function Practice.cpp */
/*
A circular swimming pool is shown in the figure below. Now we need to build a circular walkway around it and put a fence around it.
The fence price is 35 yuan/meter, and the walkway construction cost is 20 yuan/square meter.
The walkway width is 3 meters, and the pool radius is entered from the keyboard. Write a program to calculate and output the cost of the walkway and fence.

Description: A large circle contains a small circle:
The small circle is in the middle of the large circle, the small circle is the swimming pool, and the gap between the large circle and small circle is the walkway.
*/
#include <iostream>
using namespace std;
const float PI = 3.14159;
const float FencePrice = 35;
const float ConcretePrice = 20;

class Circle {
private:
  float radius;

public:
  Circle(float r);
  float Circumference() const;
  float Area() const;
};
Circle::Circle(float r) { radius = r; }

// Calculate circumference of circle
float Circle::Circumference() const { return 2 * PI * radius; }

// Calculate area of circle
float Circle::Area() const { return PI * radius * radius; }

int main(int argc, char const *argv[]) {
  float radius;
  float FenceCost, ConcreteCost;

  // Prompt user to enter radius
  cout << "Enter the radius of the pool: ";
  cin >> radius;

  // Declare Circle objects
  Circle Pool(radius);
  Circle PoolRim(radius + 3);
  // Calculate fence cost and output
  FenceCost = PoolRim.Circumference() * FencePrice;
  cout << "Fencing Cost is RMB " << FenceCost << endl;

  // Calculate walkway cost and output
  ConcreteCost = (PoolRim.Area() - Pool.Area()) * ConcretePrice;
  cout << "Concrete Cost is RMB " << ConcreteCost << endl;
  
  return 0;
}

