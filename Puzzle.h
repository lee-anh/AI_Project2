#ifndef PUZZLE_H
#define PUZZLE_H

#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "Alldiff.h"
#include "BinaryArc.h"
#include "Constraint.h"
#include "Tile.h"
#include "macros.h"

using namespace std;

class Puzzle {
 public:
  // Puzzle(string filename, puzzleType type);
  Puzzle(vector<vector<Tile*>> arr);

  // deep copy constructor
  Puzzle(Puzzle* p);

  /// @brief check if assignment complete
  /// @return
  bool isAssignmentComplete();

  Tile* getTile(int x, int y);
  Tile* getTile(string id);
  vector<vector<Tile*>> getPuzzleArr();

  void printPuzzle();
  void printPuzzleData();

 private:
  puzzleType type;
  vector<vector<Tile*>> arr;
};

#endif