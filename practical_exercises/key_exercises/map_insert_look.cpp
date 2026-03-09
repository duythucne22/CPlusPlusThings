/* Dictionary Insert and Find.cpp */
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

int main(int argc, char const *argv[]) {
  map<const char *, const char *> mp;
  map<const char *, const char *>::iterator iter;
  const char key[3][20] = {"img", "system", "ip"};
  const char value[3][20] = {"d:/a.img", "win7", "193.68.6.3"};

  // Insert using make_pair
  for (int i = 0; i < 2; i++) {
    mp.insert(make_pair(key[i], value[i]));
  }
  // Insert using pair<const char*, const char*>
  mp.insert(pair<const char *, const char *>(key[2], value[2]));

  // Array insertion method
  mp["addr"] = "China";
  // Get elements using iterator
  // Loop through elements
  for (iter = mp.begin(); iter != mp.end(); iter++) {
    cout << iter->first << "\t" << iter->second << endl;
  }
  char key1[20];
  cout << "Enter key to search: ";
  cin.getline(key1, 20);
  // Find element
  for (iter = mp.begin(); iter != mp.end(); iter++) {
    if (strcmp(iter->first, key1) == 0) {
      cout << iter->first << " found! "
           << "Corresponding value: " << iter->second << endl;
    }
  }

  // First deletion method
  // find can only be used for array-based lookups! And does not support cin input
  iter = mp.find("addr");
  if (iter != mp.end()) {
    cout << iter->first << " found by key! "
         << "Corresponding value: " << iter->second << endl;
    cout << "Starting to delete element!" << endl;
    mp.erase(iter);
    // break;
  }
  // Second deletion method
  // Delete by key
  char drop_key[20];
  // Delete by value
  char drop_value[20];
  cout << "Enter key to delete: ";
  cin.getline(drop_key, 20);
  cout << "Enter value to delete: ";
  cin.getline(drop_value, 20);
  for (iter = mp.begin(); iter != mp.end(); iter++) {
    if (strcmp(iter->first, drop_key) == 0) {
      cout << iter->first << " found by key! "
           << "Corresponding value: " << iter->second << endl;
      cout << "Starting to delete element!" << endl;
      mp.erase(iter);
      break;
    }
    if (strcmp(iter->second, drop_value) == 0) {
      cout << iter->second << " value found! "
           << "Corresponding key: " << iter->first << endl;
      cout << "Starting to delete element!" << endl;
      mp.erase(iter);
      break;
    }
  }
  cout << "------After deleting elements--------\n";
  // Loop through elements
  for (iter = mp.begin(); iter != mp.end(); iter++) {
    cout << iter->first << "\t" << iter->second << endl;
  }
  
  return 0;
}
