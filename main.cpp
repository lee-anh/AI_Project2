#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Control.h"

int main(int argc, char* argv[]) {
  Control* p = new Control("./Sudoku/standard/puzzle1.txt", STANDARD);

  //  p->printPuzzleData();
  p->printPuzzle();
  //  p->printConstraintsMap();
  p->ac3();

  // p->printPuzzleData();
  p->printPuzzle();

  return 0;
}