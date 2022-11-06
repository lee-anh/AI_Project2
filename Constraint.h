#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <iostream>
#include <vector>

#include "BinaryArc.h"
#include "Sum.h"
#include "Tile.h"
using namespace std;

class Constraint {
 public:
  Constraint(int targetSum, vector<Tile*> tiles);
  Constraint(Tile* t1, Tile* t2);

  pair<int, int> getTile1();
  pair<int, int> getTile2();
  vector<Tile*> getTiles();
  bool revise();
  bool proposeAssignment(string tileId, int x);
  bool willChangeDomainOfOtherTiles(string tileId, int x);
  vector<pair<Tile*, vector<int>>> removeFromDomainOfOtherTiles(string tileId, int x);

 private:
  bool isBinary;
  Sum* s; 
  BinaryArc* b; 
};

#endif