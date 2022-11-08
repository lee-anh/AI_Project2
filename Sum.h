#ifndef SUM_H
#define SUM_H

#include <iostream>
#include <vector>

#include "Constraint.h"
#include "Tile.h"

using namespace std;

/// @brief the Sum class completes the virtual Constraint interface
/// it represents a constraint where the tiles must sum to a target sum
class Sum : virtual public Constraint {
 public:
  /// @brief Sum constructor
  /// @param targetSum what the value of the tiles should add up to
  /// @param tiles tiles associated with this sum constraint
  Sum(int targetSum, vector<Tile*> tiles);

  /// @brief virtual function, used in checkConsistent to check if the assignment of tile is consistent with the domains of the neighboring tiles
  /// @param tileId id of tile to propose assignment of
  /// @param x value to propose
  /// @return true if the assignment would be consistent, false if not
  bool proposeAssignment(string tileId, int x);

  /// @brief virtual function, used in orderDomainValues
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
  int targetSum;
  vector<Tile*> tiles;
};

#endif