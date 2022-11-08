#include "Sum.h"

/// @brief Sum constructor
/// @param targetSum what the value of the tiles should add up to
/// @param tiles tiles associated with this sum constraint
Sum::Sum(int targetSum, vector<Tile*> tiles) {
  this->targetSum = targetSum;
  this->tiles = tiles;
  // cout << "sum constructor: tilesSize: " << tiles.size() << endl;
}

/// @brief virtual function, used in checkConsistent to check if the assignment of tile is consistent with the domains of the neighboring tiles
/// @param tileId id of tile to propose assignment of
/// @param x value to propose
/// @return true if the assignment would be consistent, false if not
bool Sum::proposeAssignment(string tileId, int x) {
  // TODO: can put stronger logic here
  int currentTotal = 0;
  vector<Tile*> otherUnassigned;
  for (Tile* t : tiles) {
    currentTotal += t->getNum();
    if (t->getNum() == 0 && t->getId() != tileId) otherUnassigned.push_back(t);
  }

  int sumWouldBe = currentTotal + x;
  if (sumWouldBe > targetSum) return false;
  int newTarget = targetSum - sumWouldBe;
  if ((int)otherUnassigned.size() == 0) {
    if (newTarget == 0) return true;
    return false;
  }

  if ((int)otherUnassigned.size() == 1) {
    for (int a : otherUnassigned.at(0)->getDomain()) {
      if (a == newTarget) return true;
    }
    return false;
  }

  // ideally would DP this up to be an n-sum problem
  // maybe we'll just check for 2 sum
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

/// @brief virtual function, used in orderDomainValues (LCV)
/// @param tileId id of tile to check the neighbors of
/// @param x value to propose
/// @return true if assignment will change the domains of the neighbors
bool Sum::willChangeDomainOfOtherTiles(string tileId, int x) {
  int currentTotal = 0;

  // we should only check the tiles that haven't been assigned yet
  vector<Tile*> otherUnassigned;
  for (Tile* t : tiles) {
    currentTotal += t->getNum();
    if (t->getNum() == 0 && t->getId() != tileId) otherUnassigned.push_back(t);
  }

  int left = (targetSum + x) - currentTotal;

  if ((int)otherUnassigned.size() == 0) {
    if (left == 0) return false;
  }

  if ((int)otherUnassigned.size() == 1) {
    for (int a : otherUnassigned.at(0)->getDomain()) {
      if (a != left) return true;
    }
    return false;
  }

  // ideally would DP this up to be an n-sum problem
  // maybe we'll just check for 2 sum

  if ((int)otherUnassigned.size() == 2) {
    vector<int> domain1 = otherUnassigned.at(0)->getDomain();
    vector<int> domain2 = otherUnassigned.at(1)->getDomain();
    vector<int> stay1;  // could have duplicates
    vector<int> stay2;  // could have duplicates
    for (int i : domain1) {
      for (int j : domain2) {
        if (i + j == left) {
          stay1.push_back(i);  // this is an acceptable value
          stay2.push_back(j);
        }
      }
    }

    for (int i : domain1) {
      bool found = false;
      for (int j : stay1) {
        if (i == j) {
          found = true;
          break;
        }
      }
      if (found == false) return true;  // edits are needed
    }

    for (int i : domain2) {
      bool found = false;
      for (int j : stay2) {
        if (i == j) {
          found = true;
          break;
        }
      }
      if (found == false) return true;  // edits are needed
    }
    return false;
  }

  // this could be stronger for sure
  for (Tile* t : otherUnassigned) {
    for (int a : t->getDomain()) {
      if (a > left) return true;
    }
  }

  return false;
}

/// @brief  removes x from the domain of tileId's neighbors, used in forward check
/// @param tileId tile id of the tile to check the neighbors of
/// @param x
/// @return a pair, where the first value is true if a valid assignment could still happen after x is removed from the domain
// and the second value is vector of the old domains
pair<bool, vector<pair<Tile*, vector<int>>>> Sum::removeFromDomainOfOtherTiles(string tileId, int x) {
  // TODO: this one is breaking the code :(
  //  cout << "sum forward check for " << tileId << " assign: " << x << endl;
  vector<pair<Tile*, vector<int>>> oldDomains;

  int currentTotal = 0;
  vector<Tile*> otherUnassigned;
  for (Tile* t : tiles) {
    if (tileId != t->getId()) {
      currentTotal += t->getNum();
      if (t->getNum() == 0) otherUnassigned.push_back(t);
    }
  }

  int newTarget = targetSum - x - currentTotal;
  // cout << "target: " << targetSum << " x: " << x << " current: " << currentTotal << " newTarget: " << newTarget << " # unassigned: " << otherUnassigned.size() << endl;
  // detect some basic inconsistencies
  if (otherUnassigned.size() == 0 && newTarget != 0) {
    return make_pair(false, oldDomains);
  }

  if (otherUnassigned.size() == 1) {
    Tile* t = otherUnassigned.at(0);
    //  cout << " tile change: " << t->getId() << endl;
    vector<int> domain = t->getDomain();
    oldDomains.push_back(make_pair(t, t->getDomain()));
    vector<int> toRemove;
    for (int a : domain) {
      if (a != newTarget) toRemove.push_back(a);
      // check for no more domain size?
    }
    if (toRemove.size() == t->getDomainSize()) {
      //  cout << "would 0 domain" << endl;
      return make_pair(false, oldDomains);
    }

    for (int b : toRemove) {
      t->removeFromDomain(b);
    }
  }
  /*
  if ((int)otherUnassigned.size() == 2) {
    vector<int> domain1 = otherUnassigned.at(0)->getDomain();
    vector<int> domain2 = otherUnassigned.at(1)->getDomain();
    oldDomains.push_back(make_pair(t, t->getDomain()));
    oldDomains.push_back(make_pair(t, t->getDomain()));
    for (int i : domain1) {
      for (int j : domain2) {
        if (i + j == newTarget) return true;
      }
    }
    return false;
  }

  // I think we just have to be smarter about this
  for (Tile* t : otherUnassigned) {
    //  cout << t->getId() << " ";
    oldDomains.push_back(make_pair(t, t->getDomain()));

    vector<int> domain = t->getDomain();

    // TODO: check if it's empty
    for (int a : domain) {
      if (a > newTarget) t->removeFromDomain(a);
      if (t->getDomainSize() == 0) cout << "Domain size is 0!!!" << endl;
    }
  }

  cout << endl;
  */

  return make_pair(true, oldDomains);
}

/// @brief get the Tiles associated with this
/// @return
vector<Tile*> Sum::getTiles() {
  //  cout << "sum ";
  return tiles;
}

// just here to complete the virtual interface. Since the sum constraint isn't binary it won't be used
bool Sum::revise() {
  return false;
}
