#ifndef PUZZLE_NODE
#define PUZZLE_NODE

#include <iostream>

#include "Puzzle.h"

using namespace std;

class PuzzleNode {
 public:
  PuzzleNode(Puzzle* p);
  Puzzle* getPuzzle();
  vector<PuzzleNode*> getChildren();
  // TODO: we'll need to add children eventually

 private:
  Puzzle* p;
  vector<PuzzleNode*> children;
};

#endif