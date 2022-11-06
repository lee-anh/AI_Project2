#ifndef SUM_H
#define SUM_H

#include <iostream>
#include <vector>

#include "Tile.h"

using namespace std;

class Sum {
 public:
  Sum(Tile* t1, Tile* t2);
  Sum(int targetSum, vector<Tile*> tiles);
  // int getTargetSum();
  vector<Tile*> getTiles();

  // these are the implementations of the virtual functions
  bool proposeAssignment(string tileId, int x);
  bool willChangeDomainOfOtherTiles(string tileId, int x);
  vector<pair<Tile*, vector<int>>> removeFromDomainOfOtherTiles(string tileId, int x);

  // just here to finish implementing the virtual class
  pair<int, int> getTile1();
  pair<int, int> getTile2();
  bool revise();

 private:
  int targetSum;
  vector<Tile*> tiles;
};

#endif