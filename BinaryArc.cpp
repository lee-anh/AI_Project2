#include "BinaryArc.h"

/// @brief Binary Arc Constructor
/// @param t1 tile 1
/// @param t2 tile 2
BinaryArc::BinaryArc(Tile* t1, Tile* t2) {
  this->t1 = t1;
  this->t2 = t2;
}

/// @brief used in checkConsistent to check if the assignment of tile is consistent with the domains of the neighboring tiles
/// check that the assignment of tile 2 is not equal to the proposed value
/// @param tileId id of tile to propose assignment of
/// @param x value to propose
/// @return true if the assignment would be consistent, false if not
bool BinaryArc::proposeAssignment(string tileId, int x) {
  // we can ignore tileId b/c we only have one other tile
  if ((t2->getNum() != 0) && (x == t2->getNum())) return false;
  return true;
}

/// @brief used in orderDomainValues
/// if x is in domain2, then return true, else return false
/// @param tileId id of tile to check the neighbors of
/// @param x value to propose
/// @return true if assignment will change the domains of the neighbors
bool BinaryArc::willChangeDomainOfOtherTiles(string tileId, int x) {
  if (t2->isInDomain(x)) return true;
  return false;
}

/// @brief  removes x from the domain of tileId's neighbors, used in forward check
/// removes x from the domain of tile 2 if tile 2 is unassigned
/// @param tileId tile id of the tile to check the neighbors of
/// @param x
/// @return a pair, where the first value is true if a valid assignment could still happen after x is removed from the domain
// and the second value is vector of the old domains
pair<bool, vector<pair<Tile*, vector<int>>>> BinaryArc::removeFromDomainOfOtherTiles(string tileId, int x) {
  // cout << "bin forward check for " << tileId << " assign: " << x << endl;
  vector<pair<Tile*, vector<int>>> oldDomains;
  // cout << t2->getId() << " " << endl;
  if (t2->getNum() == 0) {  // unassigned
    oldDomains.push_back(make_pair(t2, t2->getDomain()));
    t2->removeFromDomainNoSet(x);
  }
  return make_pair(true, oldDomains);
}

/// @brief revise the tiles between the two domains, used for ac3
/// @return true if a revision was made, false if not
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

/// @brief get the Tiles associated with this
/// @return
vector<Tile*> BinaryArc::getTiles() {
  // cout << "bin ";
  vector<Tile*> toReturn;
  toReturn.push_back(t1);
  toReturn.push_back(t2);
  return toReturn;
}
