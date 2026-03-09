/* Output Format.cpp */
#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  char s[20] = "this is a string";
  double digit = -36.96656;
  cout << setw(30) << left << setfill('*') << s << endl;
  cout << dec << setprecision(4) << digit << endl;
  cout << dec << 15 << endl;
  // setbase(int x) sets the base, after which all operations use this base for calculation!
  cout << setbase(10) << 15 << endl;
  // Round to nearest integer, keep 2 decimal places
  float x = 6.6937;
  cout << float(int(x * 1000 + 0.5) / 1000.0) << endl;
  
  return 0;
}
