#ifndef ALLDIFF_H
#define ALLDIFF_H

#include <iostream>
#include <vector>

#include "BinaryArc.h"
#include "Tile.h"
#include "macros.h"

using namespace std;

/// @brief  Alldiff represents a constraint where all the Tiles must have different values
class Alldiff {
 public:
  /// @brief Constructor
  /// @param pArr puzzle array (array of tiles)
  /// @param g the type of group it is in ex. box, col, row
  /// @param x the x coordinate of the left/upper most tile
  /// @param y the y coordinate of the left/upper
  Alldiff(vector<vector<Tile*>> pArr, group g, int x, int y);  // don't need to do any thing

  /// @brief convert an Alldiff to Binary Arcs
  /// @return vector of tile id and BinaryArcs
  vector<pair<string, BinaryArc*>> toBinaryArcs();

  /// @brief print out the tile ids associated with this constraint
  void printAlldiff();

 private:
  vector<Tile*> arr;
  vector<vector<Tile*>> pArr;
  group g;
  int x;
  int y;

  /// @brief create an alldiff for a box
  void initBox();

  /// @brief create an alldiff for a column
  void initCol();

  /// @brief create an alldiff for a row
  void initRow();
};

#endif