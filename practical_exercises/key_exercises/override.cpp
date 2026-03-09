/* Inheritance and Encapsulation.cpp */
#include <cstring>
#include <iostream>

using namespace std;
class Employee {
public:
  Employee(const char *name, const char *id) {
    strcpy(Name, name);
    strcpy(Id, id);
  }
  char *getName() { return Name; }
  char *getId() { return Id; }
  void display() { cout << Name << "\t" << Id << endl; }

private:
  char Name[20];
  char Id[20];
};

class Manager : public Employee {
public:
  // Directly call constructor to pass, base class constructor has parameters, derived class must pass parameters through constructor in initialization list
  Manager(const char *name, const char *id, int week) : Employee(name, id) {
    WeeklySalary = week * 1000;
  }
  void display() {
    cout << "Manager: " << getName() << "\t" << getId() << "\t" << WeeklySalary
         << endl;
  }

private:
  int WeeklySalary;
};

class SaleWorker : public Employee {
public:
  SaleWorker(const char *name, const char *id, int profit, int x)
      : Employee(name, id) {
    workerMoney = baseMoney + x * 0.05 * profit;
  }
  void display() {
    cout << "Salesperson: " << getName() << "\t" << getId() << "\t" << workerMoney
         << endl;
  }

private:
  float baseMoney = 800.0;
  float workerMoney;
};
class HourWorker : public Employee {
public:
  HourWorker(const char *name, const char *id, int h) : Employee(name, id) {
    TotalMoney = h * hourMoney;
  }
  void display() {
    cout << "Hourly Worker: " << getName() << "\t" << getId() << "\t" << TotalMoney
         << endl;
  }

private:
  float hourMoney = 100.0;
  float TotalMoney;
};

int main(int argc, char const *argv[]) {
  cout << "Please enter work weeks: ";
  int week;
  cin >> week;
  Manager m("Xiao Wang", "11111111", week);
  m.display();
  cout << "Please enter sales profit: ";
  int profit;
  cin >> profit;
  cout << "Please enter number of items sold: ";
  int x;
  cin >> x;
  SaleWorker s("Xiao Li", "222222", profit, x);
  s.display();
  cout << "Please enter work hours: ";
  int hour;
  cin >> hour;
  HourWorker h("Xiao He", "333333", hour);
  h.display();
  
  return 0;
}
