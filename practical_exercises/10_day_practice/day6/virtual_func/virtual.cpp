/* Virtual Function Example.cpp */

// Eg7-1.cpp
// When a base class pointer or reference points to a derived class object, the difference between virtual and non-virtual functions:
// If Employee's print is declared as virtual, you can access Manager's print function; if not virtual, you can only access Employee's print
#include <iostream>
#include <string>
using namespace std;
class Employee {
public:
  Employee(string name, string id);
  string getName();
  string getId();
  float getSalary();
  virtual void print();

private:
  string Name;
  string Id;
};
Employee::Employee(string name, string id) {
  Name = name;
  Id = id;
}
string Employee::getName() { return Name; }
string Employee::getId() { return Id; }
float Employee::getSalary() { return 0.0; }
void Employee::print() {
  cout << "Name: " << Name << "\t"
       << "ID: " << Id << endl;
}

class Manager : public Employee {
public:
  Manager(string name, string id, float s = 0.0) : Employee(name, id) {
    weeklySalary = s;
  }
  void setSalary(float s) { weeklySalary = s; } // Set manager's weekly salary
  float getSalary() { return weeklySalary; }    // Get manager's weekly salary
  void print() { // Print manager's name, ID, weekly salary
    cout << "Manager: " << getName() << "\t\t ID: " << getId()
         << "\t\t Weekly Salary: " << getSalary() << endl;
  }

private:
  float weeklySalary; // Weekly salary
};

/*
Regardless of the assignment method, you can only access members inherited by the derived class from the base class through a base class object (or its pointer or reference),
and cannot access members defined in the derived class. Virtual functions allow accessing members defined in the derived class through base class pointers or references.
*/
int main() {
  Employee e("Xiao Mi", "NO0001"), *pM;
  Manager m("Xiao Wang", "NO0002", 128);
  m.print();
  pM = &m;
  pM->print();
  Employee &rM = m;
  rM.print();
  
  return 0;
}
// The essence of the virtual keyword is to inform the compiler that the function specified as virtual is compiled using dynamic binding.
