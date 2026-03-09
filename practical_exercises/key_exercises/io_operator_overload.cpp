/* Input Output Operator Overloading.cpp */
/*
   There is a sales person class Sales, with data members: name, id number, age.
   Overload input/output operators to implement input and output of Sales class data members.
 */
#include <cstring>
#include <iostream>
using namespace std;
class Sales {
private:
  char name[10];
  char id[18];
  int age;

public:
  Sales(char *Name, char *ID, int Age);

  friend Sales &operator<<(ostream &os, Sales &s); // Overload output operator
  friend Sales &operator>>(istream &is, Sales &s); // Overload input operator
};
Sales::Sales(char *Name, char *ID, int Age) {
  strcpy(name, Name);
  strcpy(id, ID);
  age = Age;
}
Sales &operator<<(ostream &os, Sales &s) {
  os << s.name << "\t"; // Output name
  os << s.id << "\t";   // Output ID number
  os << s.age << endl;  // Output age
  return s;
}
Sales &operator>>(istream &is, Sales &s) {
  cout << "Enter employee's name, ID number, age" << endl;
  is >> s.name >> s.id >> s.age;
  return s;
}
int main() {
  Sales s1("Du Kang", "214198012111711", 40); // L1
  cout << s1;                              // L2
  cout << endl;                            // L3
  cin >> s1;                               // L4
  cout << s1;                              // L5
}
