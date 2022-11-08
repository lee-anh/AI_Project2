#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Control.h"

int main(int argc, char* argv[]) {
  bool useAc3 = true;
  bool useMinRemainingValues = true;
  bool useLeastConstrainingValues = true;
  bool useForwardChecking = true;
  puzzleType type = OVERLAP;  // either STANDARD, OVERLAP, or KILLER

  // the fastest configurationss
  if (argc == 2) {
    if (stoi(argv[1]) == 1) {
      useAc3 = true;
      useMinRemainingValues = true;
      useLeastConstrainingValues = true;
      useForwardChecking = true;
      type = STANDARD;

    } else if (stoi(argv[1]) == 2) {
      useAc3 = true;
      useMinRemainingValues = true;
      useLeastConstrainingValues = true;
      useForwardChecking = true;
      type = OVERLAP;

    } else if (stoi(argv[1]) == 3) {
      useAc3 = true;
      useMinRemainingValues = false;
      useLeastConstrainingValues = true;
      useForwardChecking = false;
      type = KILLER;
    }
  }

  if (type == STANDARD) {
    for (int i = 1; i < 11; i++) {
      cout << "Puzzle " << i << "----------------------" << endl;
      Control* p = new Control("./Sudoku/standard/puzzle" + to_string(i) + ".txt", "./log/standard_data.txt", type, useAc3, useMinRemainingValues, useLeastConstrainingValues, useForwardChecking);
      p->writeDataToLog();
    }
  } else if (type == OVERLAP) {
    for (int i = 1; i < 11; i++) {
      cout << "Puzzle " << i << "-----------------------------" << endl;
      Control* p = new Control("./Sudoku/overlap/puzzle" + to_string(i) + ".txt", "./log/overlap_data.txt", type, useAc3, useMinRemainingValues, useLeastConstrainingValues, useForwardChecking);
      p->writeDataToLog();
    }
  } else if (type == KILLER) {
    for (int i = 1; i < 11; i++) {
      cout << "Puzzle " << i << "----------------------" << endl;
      Control* p = new Control("./Sudoku/killer/puzzle" + to_string(i) + ".txt", "./log/killer_data.txt", type, useAc3, useMinRemainingValues, useLeastConstrainingValues, useForwardChecking);
      p->writeDataToLog();
    }
  }

  return 0;
}