#include "Sum.h"

Sum::Sum(int targetSum, vector<Tile*> tiles) {
  this->targetSum = targetSum;
  this->tiles = tiles;
  // cout << "sum constructor: tilesSize: " << tiles.size() << endl;
}

// used in checkConsistent
bool Sum::proposeAssignment(string tileId, int x) {
  // TODO: can put stronger logic here
  int currentTotal = 0;
  vector<Tile*> otherUnassigned;
  for (Tile* t : tiles) {
    currentTotal += t->getNum();
    if (t->getNum() == 0 && t->getId() != tileId) otherUnassigned.push_back(t);
  }

  if (currentTotal + x > targetSum) return false;
  int sumWouldBe = currentTotal + x;
  int newTarget = targetSum - sumWouldBe;

  // ideally would DP this up to be an n-sum problem
  // maybe we'll just check for 2 sum
  if ((int)otherUnassigned.size() == 1) {
    for (int a : otherUnassigned.at(0)->getDomain()) {
      if (a == newTarget) return true;
    }
    return false;
  }
  if ((int)otherUnassigned.size() == 2) {
    vector<int> domain1 = otherUnassigned.at(0)->getDomain();
    vector<int> domain2 = otherUnassigned.at(1)->getDomain();
    for (int i : domain1) {
      for (int j : domain2) {
        if (i + j == newTarget) return true;
      }
    }
    return false;
  }

  return true;
}

// used in orderDomainValues
bool Sum::willChangeDomainOfOtherTiles(string tileId, int x) {
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
// this one is breaking the code
vector<pair<Tile*, vector<int>>> Sum::removeFromDomainOfOtherTiles(string tileId, int x) {
  // TODO:
  // cout << "sum forward check for " << tileId << " assign: " << x << endl;
  vector<pair<Tile*, vector<int>>> oldDomains;

  int currentTotal = 0;
  vector<Tile*> otherUnassigned;
  for (Tile* t : tiles) {
    if (tileId != t->getId()) {
      currentTotal += t->getNum();
      if (t->getNum() == 0 && t->getId() != tileId) otherUnassigned.push_back(t);
    }
  }
  // cout << "change: ";

  int newTarget = targetSum - x - currentTotal;
  for (Tile* t : otherUnassigned) {
    //  cout << t->getId() << " ";
    oldDomains.push_back(make_pair(t, t->getDomain()));
    for (int a : t->getDomain()) {
      if (a > newTarget) t->removeFromDomain(a);
    }
  }
  cout << endl;

  ////////////////////
  /*
  int currentTotal = 0;

  for (Tile* t : tiles) {
    currentTotal += t->getNum();
  }

  int left = (targetSum)-currentTotal;
  for (Tile* t : tiles) {
    if ((t->getNum() == 0) && (t->getId() != tileId)) {  // unassigned and not this tile
      oldDomains.push_back(make_pair(t, t->getDomain()));
      for (int a : t->getDomain()) {
        if (a > left) t->removeFromDomain(a);
      }
    }
  }
  */

  return oldDomains;
}

vector<Tile*> Sum::getTiles() {
  //  cout << "sum ";
  return tiles;
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
