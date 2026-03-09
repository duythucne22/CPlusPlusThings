/* Bracket Overloading.cpp */
#include <cstring>
#include <iostream>
using namespace std;
struct Person { // Structure for employee basic information
  double salary;
  char *name;
};
class SalaryManaege {
  Person *employ; // Array to store employee information
  int max;        // Upper bound of array index
  int n;          // Actual number of employees in the array
public:
  SalaryManaege(int Max = 0) {
    max = Max;
    n = 0;
    employ = new Person[max];
  }
  // The reference return feature allows direct use as lvalue
  double &operator[](char *Name) { // Overload [], return reference
    Person *p;
    for (p = employ; p < employ + n; p++)
      // If exists, handle it
      if (strcmp(p->name, Name) == 0)
        return p->salary;
    // Handle case when not exists
    p = employ + n++;
    p->name = new char[strlen(Name) + 1];
    strcpy(p->name, Name);
    p->salary = 0;
    return p->salary;
  }

  void display() {
    for (int i = 0; i < n; i++)
      cout << employ[i].name << "   " << employ[i].salary << endl;
  }
  ~SalaryManaege() { delete[] employ; }
};
int main() {
  SalaryManaege s(3);
  s["Zhang San"] = 2188.88;
  s["Li Si"] = 1230.07;
  s["Wang Wu"] = 3200.97;
  cout << "Zhang San\t" << s["Zhang San"] << endl;
  cout << "Li Si\t" << s["Li Si"] << endl;
  cout << "Wang Wu\t" << s["Wang Wu"] << endl;

  cout << "-------Below is the output of display--------\n\n";
  s.display();
}
