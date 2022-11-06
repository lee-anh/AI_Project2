#include "Alldiff.h"

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

// maybe we need to return a pair
// maybe we could add it straight to the Map
vector<pair<string, Constraint*>> Alldiff::toBinaryArcs() {
  // where are we going to add these binaries to? // we might have to handle that a level up
  // make sure to add in both directions
  vector<pair<string, Constraint*>> toReturn;
  for (int i = 0; i < 9; i++) {  // I think these bounds are right
    for (int j = 0; j < 9; j++) {
      if (i != j) {
        pair<string, Constraint*> toAdd = make_pair(arr[i]->getId(), new Constraint(arr[i], arr[j]));
        toReturn.push_back(toAdd);
      }
    }
  }

  return toReturn;
}

void Alldiff::printAlldiff() {
  cout << "Alldiff: " << endl;
  for (Tile* t : arr) {
    t->printTile();
  }
}

void Alldiff::initBox() {
  // go three across, go three down

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      arr.push_back(pArr[x + i][y + j]);
    }
  }
}

void Alldiff::initCol() {
  for (int i = 0; i < 9; i++) {
    arr.push_back(pArr[x + i][y]);
  }
}

void Alldiff::initRow() {
  for (int i = 0; i < 9; i++) {
    arr.push_back(pArr[x][y + i]);
  }
}
