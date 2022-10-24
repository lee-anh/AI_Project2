#ifndef SUM_H 
#define SUM_H 

#include <iostream>
#include <vector>

using namespace std;

class Sum {
 public:
  Sum(int target, int maxNumVal);
  Sum(int target, int maxNumVal, vector<int> start);

  bool check(int val);
  bool add(int val);
  bool remove(int val);

  // TODO: would remaining be useful?
  // int remaining();  // is this even useful?

  // what if something in the sum constraint was wrong to begin with?
  // should we allow it if the next one to add will require a dup? yes, dups are allowed
 private:
  vector<int> arr;
  int target;
  int maxNumVal;  // maximum number of values you can have in this constraint
  int currentSum;
};

#endif