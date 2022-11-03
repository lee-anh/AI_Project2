#include "BinaryArc.h"

BinaryArc::BinaryArc(Tile* t1, Tile* t2) {
  this->t1 = t1;
  this->t2 = t2;
}

bool BinaryArc::revise() {
  bool revised = false;
  vector<int> domain1 = t1->getDomain();
  vector<int> domain2 = t2->getDomain();
  for (int x : domain1) {
    int noAllowCount = 0;
    for (int y : domain2) {  // really only triggers when we already have an assignment
      if (x == y) {
        noAllowCount++;
      }
    }
    if (noAllowCount == (int)domain2.size()) {  // no value y in domain 2 allows (x, y) to satisfy NE
      t1->removeFromDomain(x);
      revised = true;
    }
  }
  return revised;
}

Tile* BinaryArc::getTile1() {
  return t1;
}

Tile* BinaryArc::getTile2() {
  return t2;
}
string BinaryArc::getId1() {
  return t1->getId();
}

string BinaryArc::getId2() {
  return t2->getId();
}

// TODO: the Constraint class should have too
bool BinaryArc::proposeAssignment(int x) {
  vector<int> domain2 = t2->getDomain();

  int allowed = 0;
  for (int y : domain2) {  // really only triggers when we already have an assignment
    if (x != y) allowed++;
  }

  if (allowed == 0) return false;
  return true;
}