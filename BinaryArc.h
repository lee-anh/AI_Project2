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
  // we need to make sure that the assignments are satisfied?
  bool revise();
  // we need both ways for the arcs

 private:
  Tile* t1;
  Tile* t2;
};

#endif