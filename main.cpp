#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Control.h"

int main(int argc, char* argv[]) {
  bool useAc3 = true;
  bool useMinRemainingValues = true;
  bool useLeastConstrainingValues = false;
  bool useForwardChecking = false;
  puzzleType type = OVERLAP;

  // without  forward checking
  // Control* p = new Control("./Sudoku/standard/puzzle6.txt", STANDARD, true, true, false, false);

  // with forward checking
  // Control* p = new Control("./Sudoku/standard/puzzle3.txt", STANDARD, true, true, false, true);
  // Control* p = new Control("./Sudoku/standard/puzzle6.txt", STANDARD, true, true, false, true);

  if (type == STANDARD) {
    for (int i = 1; i < 11; i++) {
      cout << "Puzzle " << i << "-----------------------" << endl;
      Control* p = new Control("./Sudoku/standard/puzzle" + to_string(i) + ".txt", type, useAc3, useMinRemainingValues, useLeastConstrainingValues, useForwardChecking);
      p->backtrackingSearch();
    }
  } else if (type == OVERLAP) {
    for (int i = 5; i < 7; i++) {
      cout << "Puzzle " << i << "-----------------------" << endl;
      Control* p = new Control("./Sudoku/overlap/puzzle" + to_string(i) + ".txt", OVERLAP, useAc3, useMinRemainingValues, useLeastConstrainingValues, useForwardChecking);
      p->backtrackingSearch();
    }
  }

  return 0;
}