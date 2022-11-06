#ifndef CHECKER_H
#define CHECKER_H

#include <iostream>
#include <vector>

#include "Puzzle.h"
#include "Tile.h"

using namespace std;

class Checker {
 public:
  static bool checkKiller(Puzzle* p, Puzzle* s);
  static bool checkStandard(Puzzle* p);
  static bool checkOverlap(Puzzle* p);

  static vector<Tile*> getBox(vector<vector<Tile*>> pArr, int x, int y);
  static vector<Tile*> getCol(vector<vector<Tile*>> pArr, int x, int y);
  static vector<Tile*> getRow(vector<vector<Tile*>> pArr, int x, int y);
  static bool isAllDiff(vector<Tile*> x);
};

#endif