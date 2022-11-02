#include "PuzzleNode.h"

PuzzleNode::PuzzleNode(Puzzle* p) {
  this->p = p;
}

Puzzle* PuzzleNode::getPuzzle() {
  return p;
}

vector<PuzzleNode*> PuzzleNode::getChildren() {
  return children;
}