#include "Sum.h"

Sum::Sum(int targetSum, vector<Tile*> tiles) {
  this->targetSum = targetSum;
  this->tiles = tiles;
  // cout << "sum constructor: tilesSize: " << tiles.size() << endl;
}
Sum::Sum(Tile* t1, Tile* t2) {
  targetSum = t1->getNum() + t2->getNum();
  tiles.push_back(t1);
  tiles.push_back(t2);
}
// used in checkConsistent
bool Sum::proposeAssignment(string tileId, int x) {
  // TODO: can put stronger logic here
  int currentTotal = 0;

  for (Tile* t : tiles) {
    currentTotal += t->getNum();
  }

  if (currentTotal + x > targetSum) return false;
  int sumWouldBe = currentTotal + x;
  // more advanced would be if we saw that there was a combination
  // that worked then we would assigned that - prune the tree faster

  for (Tile* t : tiles) {
    if (t->getNum() == 0 && t->getId() != tileId) {  // unassigned
      // assume the smallest domain value?
      vector<int> a = t->getDomain();
      sumWouldBe += *min_element(a.begin(), a.end());
      if (sumWouldBe > targetSum) return false;
    }
  }
  return true;
}

// used in orderDomainValues
bool Sum::willChangeDomainOfOtherTiles(string tileId, int x) {
  // TODO: this can be improved too

  int currentTotal = 0;

  for (Tile* t : tiles) {
    currentTotal += t->getNum();
  }

  int left = (targetSum + x) - currentTotal;  // TODO: not a super feeling about this

  for (Tile* t : tiles) {
    if (t->getNum() == 0 && t->getId() != tileId) {
      for (int a : t->getDomain()) {
        if (a > left) return true;
      }
    }
  }

  return false;
}

// used in forwardCheck
vector<pair<Tile*, vector<int>>> Sum::removeFromDomainOfOtherTiles(string tileId, int x) {
  // TODO:
  vector<pair<Tile*, vector<int>>> oldDomains;

  int currentTotal = 0;

  for (Tile* t : tiles) {
    currentTotal += t->getNum();
  }

  int left = (targetSum + x) - currentTotal;
  for (Tile* t : tiles) {
    if (t->getNum() == 0 && t->getId() != tileId) {  // unassigned and not this tile
      oldDomains.push_back(make_pair(t, t->getDomain()));
      for (int a : t->getDomain()) {
        if (a > left) t->removeFromDomain(a);
      }
    }
  }

  return oldDomains;
}

// these three functions are just here to finish implementing the virtual function

pair<int, int> Sum::getTile1() {
  return make_pair(0, 0);
}
pair<int, int> Sum::getTile2() {
  return make_pair(0, 0);
}
bool Sum::revise() {
  return true;
}
