#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>

using namespace std;

class Tile {
 public:
  Tile(int num, int x, int y);

  vector<int> getDomain();
  int getDomainSize();
  string getId();
  int getNum();
  void trySetNum();
  void removeFromDomain(int val);
  void printTile();

 private:
  int num;  // the number it's been assigned
  vector<int> domain;
  string id;
};

#endif