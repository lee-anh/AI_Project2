#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>

using namespace std;

class Tile {
 public:
  Tile(int num, int x, int y);

  // deep copy constructor
  Tile(Tile* t);

  vector<int> getDomain();
  int getDomainSize();
  string getId();
  int getNum();
  pair<int, int> getCoordinates();
  void setNum(int toSet);
  void restoreDomain(vector<int> old);
  void restoreDomainNoSet(vector<int> old);
  void removeFromDomain(int val);
  bool removeFromDomainNoSet(int val);
  bool isInDomain(int val);
  void printTile();

 private:
  int num;  // the number it's been assigned
  vector<int> domain;
  string id;
  pair<int, int> coordinates;

  void trySetNum();
};

struct tileLessThan {
  inline bool operator()(Tile* t1, Tile* t2) {
    return (t1->getDomainSize() < t2->getDomainSize());
  }
};

#endif