#ifndef ALLDIFF_H
#define ALLDIFF_H

#include <iostream>
#include <vector>

#include "BinaryArc.h"
#include "Tile.h"
#include "macros.h"

using namespace std;

class Alldiff {
 public:
  // need a Puzzle, a setting, and the starting tile's coordinate
  Alldiff(vector<vector<Tile*>> pArr, group g, int x, int y);  // don't need to do any thing

  vector<pair<string, BinaryArc*>> toBinaryArcs();

  // these vals are in the domain
  // so we would want to see if adding a certain val for a certain variable would be ok
  // forward checking?
  // TODO: a check function might be ok

  // actually putting a value in permanently

  void printAlldiff();

 private:
  vector<Tile*> arr;  // all the tiles in the range that must be different
  vector<vector<Tile*>> pArr;
  group g;
  int x;
  int y;

  void initBox();
  void initCol();
  void initRow();

  void toBinariesRow();  // give leftmost Tile
  void toBinariesCol();  // give topmost Tile
  void toBinariesBox();  // give top left corner Tile
};

#endif