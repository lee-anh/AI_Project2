#include "Alldiff.h"

/// @brief Constructor
/// @param pArr puzzle array (array of tiles)
/// @param g the type of group it is in ex. box, col, row
/// @param x the x coordinate of the left/upper most tile
/// @param y the y coordinate of the left/upper
Alldiff::Alldiff(vector<vector<Tile*>> pArr, group g, int x, int y) {
  this->pArr = pArr;  // basically just for reading for now
  this->g = g;
  this->x = x;
  this->y = y;
  if (g == BOX) {
    initBox();
  } else if (g == COL) {
    initCol();
  } else {  // g == ROW
    initRow();
  }
}

/// @brief convert an Alldiff to Binary Arcs
/// @return vector of tile id and BinaryArcs
vector<pair<string, BinaryArc*>> Alldiff::toBinaryArcs() {
  // make sure to add in both directions
  vector<pair<string, BinaryArc*>> toReturn;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (i != j) {
        pair<string, BinaryArc*> toAdd = make_pair(arr[i]->getId(), new BinaryArc(arr[i], arr[j]));
        toReturn.push_back(toAdd);
      }
    }
  }

  return toReturn;
}

// @brief print out the tile ids associated with this constraint
void Alldiff::printAlldiff() {
  cout << "Alldiff: " << endl;
  for (Tile* t : arr) {
    t->printTile();
  }
}

/// @brief create an alldiff for a box
void Alldiff::initBox() {
  // go three across, go three down

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      arr.push_back(pArr[x + i][y + j]);
    }
  }
}

/// @brief create an alldiff for a column
void Alldiff::initCol() {
  for (int i = 0; i < 9; i++) {
    arr.push_back(pArr[x + i][y]);
  }
}

/// @brief create an alldiff for a row
void Alldiff::initRow() {
  for (int i = 0; i < 9; i++) {
    arr.push_back(pArr[x][y + i]);
  }
}
