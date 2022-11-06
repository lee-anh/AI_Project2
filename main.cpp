#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Control.h"

int main(int argc, char* argv[]) {
  bool useAc3 = true;
  bool useMinRemainingValues = true;  // this one is causing a slow down in iller, but makes sense
  bool useLeastConstrainingValues = true;
  bool useForwardChecking = false;
  puzzleType type = KILLER;

  if (type == STANDARD) {
    for (int i = 1; i < 11; i++) {
      cout << "Puzzle " << i << "----------------------" << endl;
      Control* p = new Control("./Sudoku/standard/puzzle" + to_string(i) + ".txt", type, useAc3, useMinRemainingValues, useLeastConstrainingValues, useForwardChecking);
    }
  } else if (type == OVERLAP) {
    for (int i = 1; i < 11; i++) {
      cout << "Puzzle " << i << "-----------------------------" << endl;
      Control* p = new Control("./Sudoku/overlap/puzzle" + to_string(i) + ".txt", OVERLAP, useAc3, useMinRemainingValues, useLeastConstrainingValues, useForwardChecking);
    }
  } else if (type == KILLER) {
    for (int i = 1; i < 11; i++) {
      cout << "Puzzle " << i << "----------------------" << endl;
      Control* p = new Control("./Sudoku/killer/puzzle" + to_string(i) + ".txt", KILLER, useAc3, useMinRemainingValues, useLeastConstrainingValues, useForwardChecking);
    }
  }

  return 0;
}