#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Puzzle.h"

int main(int argc, char* argv[]) {
  Puzzle* p = new Puzzle("./Sudoku/puzzle1.txt", STANDARD);
  p->printPuzzle();

  return 0;
}