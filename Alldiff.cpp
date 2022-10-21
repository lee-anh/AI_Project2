#include "Alldiff.h"

Alldiff::Alldiff(vector<int> start) {
  arr = vector<int>(start);
}

bool Alldiff::check(int val) {
  for (int n : arr) {
    if (n == val) {
      return false;
    }
  }
  return true;
}

bool Alldiff::add(int val) {
  if (check(val)) {
    arr.push_back(val);
    return true;
  }
  return false;
}

// true if value was found and successfully removed
// false if not
bool Alldiff::remove(int val) {
  int index = -1;
  for (int i = 0; i < (int)arr.size(); i++) {
    if (arr[i] == val) {
      index = i;
      break;
    }
  }
  if (index != -1) {
    arr.erase(arr.begin(), arr.begin() + index);
    return true;
  }
  return false;
}