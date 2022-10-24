#include "BinaryArc.h"

BinaryArc::BinaryArc(Tile* t1, Tile* t2) {
  this->t1 = t1;
  this->t2 = t2;
}

// revise for AC-3
bool BinaryArc::revise() {
  bool revised = false;
  vector<int> domain1 = t1->getDomain();
  vector<int> domain2 = t2->getDomain();
  for (int x : domain1) {
    bool allow = true;
    for (int y : domain2) {
      // if no value y in domain 2 allows (x, y) to satisfy NE, then delete x from domain1
      if (x == y) {
        allow = false;
        break;
      }
    }
    if (!allow) {
      t1->removeFromDomain(x);
      revised = true;
    }
  }
  return revised;
}
