#include "BinaryArc.h"

BinaryArc::BinaryArc(Tile* t1, Tile* t2) {
  this->t1 = t1;
  this->t2 = t2;
}

// used in checkConsistent
bool BinaryArc::proposeAssignment(string tileId, int x) {
  // we can ignore tileId b/c we only have one other tile
  if ((t2->getNum() != 0) && (x == t2->getNum())) return false;
  return true;
}
// used in orderDomainValues
bool BinaryArc::willChangeDomainOfOtherTiles(string tileId, int x) {
  if (t2->isInDomain(x)) return true;
  return false;
}

// used in forwardCheck
// need to return the old domains
vector<pair<Tile*, vector<int>>> BinaryArc::removeFromDomainOfOtherTiles(string tileId, int x) {
  // cout << "bin forward check for " << tileId << " assign: " << x << endl;
  vector<pair<Tile*, vector<int>>> oldDomains;
  // cout << t2->getId() << " " << endl;
  if (t2->getNum() == 0) {  // unassigned
    oldDomains.push_back(make_pair(t2, t2->getDomain()));
    t2->removeFromDomain(x);
  }
  return oldDomains;
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

pair<int, int> BinaryArc::getTile1() {
  // return t1;

  return t1->getCoordinates();
}

pair<int, int> BinaryArc::getTile2() {
  //   return t2;
  return t2->getCoordinates();
}

vector<Tile*> BinaryArc::getTiles() {
  // cout << "bin ";
  vector<Tile*> toReturn;
  toReturn.push_back(t1);
  toReturn.push_back(t2);
  return toReturn;
}
