#ifndef BINARY_ARC_H
#define BINARY_ARC_H

#include <iostream>

#include "Constraint.h"
#include "Tile.h"

using namespace std;

// I guess we want this to be a constraint
// but eventually we'll also want some arcs
class BinaryArc : public Constraint {
 public:
  BinaryArc(Tile* t1, Tile* t2);
  // BinaryArc(string id1, string id2);
  // we need to make sure that the assignments are satisfied?

  bool revise();
  Tile* getTile1();
  Tile* getTile2();

  string getId1();
  string getId2();
  // we need both ways for the arcs

  // TODO: need to make this available for all Constraints?
  bool proposeAssignment(int x);  // how are we supposed to work with this?

 private:
  // string id1;
  // string id2;
  Tile* t1;
  Tile* t2;
};

#endif