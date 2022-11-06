#include "Sum.h"

/*
Sum::Sum(int target, int maxNumVal) {
  this->target = target;
  this->maxNumVal = maxNumVal;
  currentSum = 0;
}

Sum::Sum(int target, int numVal, vector<int> start) {
  this->target = target;
  this->maxNumVal = numVal;
  arr = vector<int>(start);
}

bool Sum::check(int val) {
  if ((int)arr.size() == maxNumVal) {
    return false;
  }
  if (val + currentSum <= target) {
    return true;
  }
  return false;
}

bool Sum::add(int val) {
  if (check(val)) {
    arr.push_back(val);
    currentSum += val;
  }
  return false;
}

bool Sum::remove(int val) {
  int index = -1;
  for (int i = 0; i < (int)arr.size(); i++) {
    if (arr[i] == val) {
      index = i;
      break;
    }
  }
  if (index != -1) {
    arr.erase(arr.begin(), arr.begin() + index);
    currentSum -= val;
    return true;
  }
  return false;
}
*/