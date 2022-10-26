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
  Puzzle(string filename, puzzleType type);
  // might need to have a deep copy constructor

  // we should probably read in the puzzle now
  // what should the puzzle even be able to do?

  // what kind of functionality do we want from this?

  // is this the level where we should start considering out constraints?
  Tile* getTile(int x, int y);
  void printConstraintsMap();
  void printPuzzle();
  void printPuzzleData();
  map<string, vector<Constraint*>> getConstraintMap();
  bool ac3();

 private:
  puzzleType type;
  // we honestly might want this to be exposed?
  vector<vector<Tile*>> arr;  // we already know the size?
  map<string, vector<Constraint*>> constraints;
  void addConstraintsStandard();
  void addToMap(pair<string, BinaryArc*> toAdd);

  void readInStandard(string filename);

  // should this be in its own file so that we can see it elsewhere

  // what about the puzzle with the
};

#endif