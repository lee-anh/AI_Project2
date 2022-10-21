#ifndef ALLDIFF
#define ALLDIFF

#include <iostream>
#include <vector>

using namespace std;

class Alldiff {
 public:
  Alldiff();  // don't need to do any thing
  Alldiff(vector<int> start);

  // can only input if allowed to

  // hypothetical
  bool check(int val);
  bool remove(int val);

  // actually putting a value in permanently
  bool add(int val);

 private:
  vector<int> arr;
};

#endif