/* File Read/Write Comprehensive Exercise.cpp */
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Person {
public:
  Person() {}
  Person(char *name, char *id, int math, int chinese, int english) {
    strcpy(Name, name);
    strcpy(Id, id);
    Math = math;
    Chinese = chinese;
    English = english;
    Sum = Math + Chinese + English;
  }

  void display() {
    cout << Name << "\t" << Id << "\t" << Math << "\t" << Chinese << "\t"
         << English << "\t" << Sum << endl;
  }

private:
  char Name[20];
  char Id[20];
  int Math;
  int Chinese;
  int English;
  int Sum;
};

int main(int argc, char const *argv[]) {
  char ch;
  char Name[20], Id[20];
  int Math, Chinese, English;
  fstream ioFile;
  ioFile.open("d:/per.dat", ios::out | ios::app);
  cout << "---------Create Student Record----------\n";
  do {
    cout << "Please enter name: ";
    cin >> Name;
    cout << "Please enter ID number: ";
    cin >> Id;
    cout << "Please enter Math score: ";
    cin >> Math;
    cout << "Please enter Chinese score: ";
    cin >> Chinese;
    cout << "Please enter English score: ";
    cin >> English;
    Person per(Name, Id, Math, Chinese, English);
    ioFile.write((char *)&per, sizeof(per));
    cout << "Continue creating record? (Y/y)  ";
    cin >> ch;
  } while (ch == 'y' || ch == 'Y');
  ioFile.close();
  ioFile.open("d://per.dat", ios::in);
  Person p;
  ioFile.read((char *)&p, sizeof(p));
  vector<Person> v;
  vector<Person>::iterator vt;
  while (!ioFile.eof()) {
    v.push_back(p);
    ioFile.read((char *)&p, sizeof(p));
  }
  ioFile.close();
  cout << "---------Output Record Information-----------" << endl;
  for (vt = v.begin(); vt != v.end(); vt++) {
    (*vt).display();
  }
  
  return 0;
}
