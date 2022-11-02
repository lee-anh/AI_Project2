#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <queue>

#include "Puzzle.h"
#include "PuzzleNode.h"

using namespace std;

class Control {
 public:
  Control(string filename, puzzleType type);
  void printConstraintsMap();
  void printPuzzle();

  bool ac3();

 private:
  PuzzleNode* root;
  puzzleType type;
  map<string, vector<Constraint*>> constraints;

  // only used for ac-3, which is only called once
  bool revise(BinaryArc* ba);
  void addConstraintsStandard();
  void addToMap(pair<string, BinaryArc*> toAdd);
  void readInStandard(string filename);
};

#endif