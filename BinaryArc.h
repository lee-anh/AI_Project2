#ifndef BINARY_ARC_H
#define BINARY_ARC_H

#include <iostream>

#include "Constraint.h"
#include "Tile.h"

using namespace std;

/// @brief creates a binary not equals constraint
/// completes the virtual Constraint class
class BinaryArc : virtual public Constraint {
 public:
  /// @brief Binary Arc Constructor
  /// @param t1 tile 1
  /// @param t2 tile 2
  BinaryArc(Tile* t1, Tile* t2);

  /// @brief used in checkConsistent to check if the assignment of tile is consistent with the domains of the neighboring tiles
  /// @param tileId id of tile to propose assignment of
  /// @param x value to propose
  /// @return true if the assignment would be consistent, false if not
  bool proposeAssignment(string tileId, int x);

  /// @brief used in orderDomainValues
  /// @param tileId id of tile to check the neighbors of
  /// @param x value to propose
  /// @return true if assignment will change the domains of the neighbors
  bool willChangeDomainOfOtherTiles(string tileId, int x);

  /// @brief  removes x from the domain of tileId's neighbors, used in forward check
  /// @param tileId tile id of the tile to check the neighbors of
  /// @param x
  /// @return a pair, where the first value is true if a valid assignment could still happen after x is removed from the domain
  // and the second value is vector of the old domains
  pair<bool, vector<pair<Tile*, vector<int>>>> removeFromDomainOfOtherTiles(string tileId, int x);

  /// @brief revise the tiles between the two domains, used for ac3
  /// @return true if a revision was made, false if not
  bool revise();

  /// @brief get the Tiles associated with this
  /// @return
  vector<Tile*> getTiles();

 private:
  Tile* t1;
  Tile* t2;
};

#endif