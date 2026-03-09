/* Clock ++ Operator Overloading.cpp */
#include <cmath>
#include <iostream>
using namespace std;

/*
 *  Clock class
 */
class Clock {
private:
  int Hour, Minute, Second;

public:
  Clock(int h = 0, int m = 0, int s = 0);
  void ShowTime();
  Clock &operator++();
  Clock operator++(int);
};

/*
 *  Clock class constructor
 */
Clock::Clock(int h, int m, int s) {
  if (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60) {
    Hour = h;
    Minute = m;
    Second = s;
  } else
    cout << "Input time format error!" << endl;
}

/*
 *  Display time
 */
void Clock::ShowTime() {
  cout << Hour << ":" << Minute << ":" << Second << endl;
}

/*
 *  Increment time by one second (overload prefix ++ operator)
 */
Clock &Clock::operator++() {
  Second++;
  if (Second >= 60) {
    Second = Second - 60;
    Minute++;
    if (Minute >= 60) {
      Minute = Minute - 60;
      Hour++;
      Hour = Hour % 24;
    }
  }
  return *this;
}

/*
 *  Increment time by one second (overload postfix ++ operator)
 */
Clock Clock::operator++(int) {
  Clock old = *this;
  ++(*this);
  return old;
}

/*
 *  Main function
 */
int main() {
  Clock myClock(23, 59, 59);
  cout << "Initial display time:\t\t";
  myClock.ShowTime();

  cout << "After myClock++ time:\t";

  // First execute ShowTime(), output myClock=23:59:59,
  // Then execute myClock++, now myClock=00:00:00
  (myClock++).ShowTime();

  cout << "After ++myClock time:\t";

  // First execute ++myClock, now myClock=00:00:01
  // Then execute ShowTime(), output myClock=00:00:01
  (++myClock).ShowTime();
  
}
