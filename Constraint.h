#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <iostream>
#include <vector>

#include "Tile.h"
using namespace std;

/// @brief Constraint is a virtual class that acts as an interface
class Constraint {
 public:
  Constraint();
  ~Constraint();

  /// @brief virtual function, used in checkConsistent to check if the assignment of tile is consistent with the domains of the neighboring tiles
  /// @param tileId id of tile to propose assignment of
  /// @param x value to propose
  /// @return true if the assignment would be consistent, false if not
  bool virtual proposeAssignment(string tileId, int x) = 0;

  /// @brief virtual function, used in orderDomainValues
  /// @param tileId id of tile to check the neighbors of
  /// @param x value to propose
  /// @return true if assignment will change the domains of the neighbors
  bool virtual willChangeDomainOfOtherTiles(string tileId, int x) = 0;

  /// @brief  removes x from the domain of tileId's neighbors, used in forward check
  /// @param tileId tile id of the tile to check the neighbors of
  /// @param x
  /// @return a pair, where the first value is true if a valid assignment could still happen after x is removed from the domain
  // and the second value is vector of the old domains
  pair<bool, vector<pair<Tile*, vector<int>>>> virtual removeFromDomainOfOtherTiles(string tileId, int x) = 0;

  /// @brief revise the tiles between the two domains, used for ac3
  /// @return true if a revision was made, false if not
  bool virtual revise() = 0;

  /// @brief get the Tiles associated with this
  /// @return
  vector<Tile*> virtual getTiles() = 0;
};

#endif