#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>

using namespace std;

/// @brief the Tile class represents and individual cell on the sudoku board,
/// encapsulates the domain of possible values and the actual assignment, if any
class Tile {
 public:
  /// @brief Tile Constructor
  /// @param num the value assigned to the tile, 0 if no number has been assigned yet
  /// @param x coordinate of the tile
  /// @param y coordinate of the tile
  Tile(int num, int x, int y);

  /// @brief Deep copy Constructor
  /// @param t tile to make deep copy of
  Tile(Tile* t);

  /// @brief get the domain of possible values for the tile
  /// @return
  vector<int> getDomain();

  /// @brief get the current domain size
  /// @return
  int getDomainSize();

  /// @brief get the tile's id
  /// @return
  string getId();

  /// @brief get the tile's current assignment
  /// @return
  int getNum();

  /// @brief get the tile's coordinates
  /// @return
  pair<int, int> getCoordinates();

  /// @brief set the assignment of the block
  /// @param toSet assignment
  void setNum(int toSet);

  /// @brief restore the domain, possibly setting a value if the domain is 1
  /// @param old domain
  void restoreDomain(vector<int> old);

  /// @brief restore the domain without resetting the value
  /// @param old domain
  void restoreDomainNoSet(vector<int> old);

  /// @brief remove val from domain, possibly setting the tile if the domain becomes 1
  /// @param val
  void removeFromDomain(int val);

  /// @brief remove val from domain, without setting a value
  /// @param val
  /// @return
  bool removeFromDomainNoSet(int val);

  /// @brief check to see if val is in. domain
  /// @param val
  /// @return true if val is in domain, false if not
  bool isInDomain(int val);

  /// @brief print tile data
  void printTile();

 private:
  int num;  // the number it's been assigned
  vector<int> domain;
  string id;
  pair<int, int> coordinates;

  /// @brief try to set the number of the tile if the domain becomes 1
  void trySetNum();
};

/// @brief struct for overloading the comparison of two tiles based on their domain sizes
struct tileLessThan {
  inline bool operator()(Tile* t1, Tile* t2) {
    return (t1->getDomainSize() < t2->getDomainSize());
  }
};

#endif