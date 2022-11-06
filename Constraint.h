#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <iostream>
#include <vector>
using namespace std;

class Constraint {
 public:
  // what would a Constraint need?

  virtual bool proposeAssignment(string tileId, int proposal);
  virtual bool willChangeDomainOfOtherTiles(string tileId, int x);
  virtual void removeFromDomainOfOtherTiles(string tileId, int x);
 
};

#endif