#ifndef CHECKER_H
#define CHECKER_H

#include <iostream>
#include <vector>

#include "Puzzle.h"
#include "Tile.h"

using namespace std;

/// @brief Static class to check that a puzzle has reached the solution state
class Checker {
 public:
  /// @brief  Check killer puzzle against solution
  /// @param p puzzle
  /// @param s solution
  /// @return true if all the tile values in puzzle and solution match
  static bool checkKiller(Puzzle* p, Puzzle* s);

  /// @brief Check if a standard puzzle satisfies all the constraints
  /// @param p puzzle
  /// @return true if puzzle is a solution
  static bool checkStandard(Puzzle* p);

  /// @brief Check if an overlapping puzzle satisfies all the constraints
  /// @param p puzzle
  /// @return true if puzzle is a solution
  static bool checkOverlap(Puzzle* p);

 private:
  /// @brief get all the tiles associated with a box
  /// @param pArr puzzle
  /// @param x coordinate of upper most tile
  /// @param y coordinate of left most tile
  /// @return
  static vector<Tile*> getBox(vector<vector<Tile*>> pArr, int x, int y);

  /// @brief get all the tiles associated with  a column
  /// @param pArr puzzle
  /// @param x coordinate of upper most tile
  /// @param y coordinate of left most tile
  /// @return
  static vector<Tile*> getCol(vector<vector<Tile*>> pArr, int x, int y);

  /// @brief get all the tiles associated with a row
  /// @param pArr puzzle
  /// @param x coordinate of upper most tile
  /// @param y coordinate of left most tile
  /// @return
  static vector<Tile*> getRow(vector<vector<Tile*>> pArr, int x, int y);

  /// @brief helper function for checkStandard and checkOverlap. Checks one Alldiff constraint
  /// @param x vector of Tiles to check AllDiff of
  /// @return true if Tile values are AllDiff
  static bool isAllDiff(vector<Tile*> x);
};

#endif