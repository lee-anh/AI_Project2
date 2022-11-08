#ifndef PUZZLE_H
#define PUZZLE_H

#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "Alldiff.h"
#include "BinaryArc.h"
#include "Constraint.h"
#include "Tile.h"
#include "macros.h"

using namespace std;

/// @brief the Puzzle class represents the board of a Sudoku puzzle
class Puzzle {
 public:
  /// @brief Puzzle Constructor
  /// @param arr array of tiles representing the board
  Puzzle(vector<vector<Tile*>> arr);

  /// @brief Deep copy constructor
  /// @param p
  Puzzle(Puzzle* p);

  /// @brief check if assignment complete
  /// @return true if all the tiles have assigned values
  bool isAssignmentComplete();

  /// @brief get the number of tiles that were initially unassigned
  /// @return
  int getInitialNumUnassigned();

  /// @brief get the current number of tiles that are unassigned
  /// @return the current number of unassigned tiles
  int numUnassigned();

  /// @brief get the average domain size of unassigned tiles
  /// @return the average number of elements in the domain
  float getAverageDomainSize();

  /// @brief get a tile given x and y coordinate
  /// @param x coordinate
  /// @param y coordinate
  /// @return Tile object
  Tile* getTile(int x, int y);

  /// @brief get a tile given x and y coordinate in a pair
  /// @param coordinate
  /// @return Tile object
  Tile* getTile(pair<int, int> coordinate);

  /// @brief get the underlying array of Tiles
  /// @return
  vector<vector<Tile*>> getPuzzleArr();

  /// @brief print the puzzle
  void printPuzzle();

  /// @brief print the data of each Tile in the puzzle
  void printPuzzleData();

 private:
  puzzleType type;
  vector<vector<Tile*>> arr;
  int initialNumUnassigned;
};

#endif