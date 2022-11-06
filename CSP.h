#ifndef CSP_H
#define CSP_H

#include <iostream>
#include <map>
#include <vector>

#include "Alldiff.h"
#include "BinaryArc.h"
#include "Constraint.h"
#include "Puzzle.h"
#include "Sum.h"
#include "Tile.h"

using namespace std;

class CSP {
 public:
  CSP(Puzzle* puzzle);
  map<string, vector<Constraint*>> getMap();
  vector<Constraint*> findConstraints(string tileId);
  void addConstraintsStandard();
  void addConstraintsOverlap();
  void addBinaryArcToMap(pair<string, BinaryArc*> toAdd);
  void addSumConstraintsToMap(vector<Sum*> sums);
  void addSumToMap(pair<string, Sum*> toAdd);
  void printMap();

 private:
  map<string, vector<Constraint*>> constraints;
  Puzzle* puzzle;
};

#endif