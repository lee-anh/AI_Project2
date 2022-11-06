#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <iostream>
#include <vector>

#include "Tile.h"
using namespace std;

class Constraint {
 public:
  Constraint();
  ~Constraint();
 //  Constraint(int targetSum, vector<Tile*> tiles);
  // Constraint(Tile* t1, Tile* t2);

  pair<int, int> virtual getTile1() = 0;
  pair<int, int> virtual getTile2() = 0;
  vector<Tile*> virtual getTiles() = 0;
  bool virtual revise() = 0;
  bool virtual proposeAssignment(string tileId, int x) = 0;
  bool virtual willChangeDomainOfOtherTiles(string tileId, int x) = 0;
  vector<pair<Tile*, vector<int>>> virtual removeFromDomainOfOtherTiles(string tileId, int x) = 0;
};

#endif