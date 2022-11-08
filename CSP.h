#ifndef CSP_H
#define CSP_H

#include <iostream>
#include <map>
#include <vector>

#include "Alldiff.h"
#include "BinaryArc.h"
#include "Constraint.h"
#include "Puzzle.h"
#include "Sum.h"
#include "Tile.h"

using namespace std;

/// @brief CSP encapsulates a map of constraints
/// keys are the tileIds
/// values are the associated Constraints
class CSP {
 public:
  /// @brief CSP constructor
  /// @param puzzle to create map for
  CSP(Puzzle* puzzle);

  /// @brief get the underlying map
  /// @return
  map<string, vector<Constraint*>> getMap();

  /// @brief get all the constraints (value) given a tileId (key)
  /// @param tileId the id of the tile to find the constraints of
  /// @return the value (vector of Constraints)
  vector<Constraint*> findConstraints(string tileId);

  /// @brief add Alldiff constraints for a Standard puzzle to the map
  void addConstraintsStandard();

  /// @brief add Alldiff constraints for a Overlapping puzzle to the map
  void addConstraintsOverlap();

  /// @brief add a BinaryArc to the map
  /// @param toAdd a piar of a TileId and a BinaryArc to add
  void addBinaryArcToMap(pair<string, BinaryArc*> toAdd);

  /// @brief add a vector of Sum to the map
  /// @param sums a vector of Sums to add
  void addSumConstraintsToMap(vector<Sum*> sums);

  /// @brief print the constraints in the map
  void printMap();

 private:
  map<string, vector<Constraint*>> constraints;
  Puzzle* puzzle;

  /// @brief add one sum constraint to the map
  /// @param toAdd a pair of tile id and Sum Constraint to add
  void addSumToMap(pair<string, Sum*> toAdd);
};

#endif