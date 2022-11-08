#include "Tile.h"

/// @brief Tile Constructor
/// @param num the value assigned to the tile, 0 if no number has been assigned yet
/// default adds domain {1,...,9} for unassigned tiles
/// @param x coordinate of the tile
/// @param y coordinate of the tile
Tile::Tile(int num, int x, int y) {
  this->num = num;
  if (num == 0) {  // we don't know the assignment ahead of time
    for (int i = 1; i < 10; i++) {
      domain.push_back(i);
    }
  } else {
    domain.push_back(num);  // the domain should just be that number
  }
  id = to_string(x) + "-" + to_string(y);
  coordinates = make_pair(x, y);
}

/// @brief Deep copy Constructor
/// @param t tile to make deep copy of
Tile::Tile(Tile* t) {
  this->num = t->num;
  this->domain = t->domain;
  this->id = t->id;
}

/// @brief get the domain of possible values for the tile
/// @return
vector<int> Tile::getDomain() {
  return domain;
}

/// @brief get the current domain size
/// @return
int Tile::getDomainSize() {
  return (int)domain.size();
}
/// @brief get the tile's id
/// @return
string Tile::getId() {
  return id;
}

/// @brief get the tile's current assignment
/// @return
int Tile::getNum() {
  return num;
}

/// @brief get the tile's coordinates
/// @return
pair<int, int> Tile::getCoordinates() {
  return coordinates;
}

/// @brief set the assignment of the block
/// @param toSet assignment
void Tile::setNum(int toSet) {
  // make sure that the assignment is not zero?
  if (num != 0) return;  // number is already set
  num = toSet;
  // fix domain accordingly
  domain.clear();
  domain.push_back(num);
}

/// @brief restore the domain, possibly setting a value if the domain is 1
/// @param old domain
void Tile::restoreDomain(vector<int> old) {
  num = 0;
  domain = old;
}

/// @brief restore the domain without resetting the value
/// @param old domain
void Tile::restoreDomainNoSet(vector<int> old) {
  num = 0;
  domain = old;
}

/// @brief remove val from domain, possibly setting the tile if the domain becomes 1
/// @param val
void Tile::removeFromDomain(int val) {
  int index = -1;
  for (int i = 0; i < (int)domain.size(); i++) {
    if (domain[i] == val) {
      index = i;
      break;
    }
  }
  if (index != -1) {
    domain.erase(domain.begin() + index);
    trySetNum();
  }
}

/// @brief remove val from domain, without setting a value
/// @param val
/// @return
bool Tile::removeFromDomainNoSet(int val) {
  int index = -1;
  for (int i = 0; i < (int)domain.size(); i++) {
    if (domain[i] == val) {
      index = i;
      break;
    }
  }
  if (index != -1) {
    domain.erase(domain.begin() + index);
  }
  if (domain.size() == 0) {
    // cout << "remove from domain, now size is 0" << endl;
    return false;
  }
  return true;
}

/// @brief check to see if val is in. domain
/// @param val
/// @return true if val is in domain, false if not
bool Tile::isInDomain(int val) {
  for (int x : domain) {
    if (x == val) return true;
  }
  return false;
}

/// @brief print tile data
void Tile::printTile() {
  cout << "Id: " << id << " Assignment: " << num << " Domain: ";
  for (int i = 0; i < (int)domain.size(); i++) {
    cout << domain[i] << " ";
  }
  cout << endl;
}

/// @brief try to set the number of the tile if the domain becomes 1
void Tile::trySetNum() {
  if ((int)domain.size() == 1) {
    num = domain[0];
  }
  // else we don't assign num yet
}
