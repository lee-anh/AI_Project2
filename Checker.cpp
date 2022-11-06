#include "Checker.h"

bool Checker::checkKiller(Puzzle* p, Puzzle* s) {
  vector<vector<Tile*>> a = p->getPuzzleArr();
  vector<vector<Tile*>> b = s->getPuzzleArr();
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (a[i][j]->getNum() != b[i][j]->getNum()) return false;
    }
  }
  return true;
}

bool Checker::checkStandard(Puzzle* p) {
  // make sure that all the constraints have been satisfied
  vector<vector<Tile*>> a = p->getPuzzleArr();
  for (int i = 0; i < 9; i++) {
    // for each row
    if (!isAllDiff(getCol(a, 0, i))) return false;
    if (!isAllDiff(getRow(a, i, 0))) return false;

    // for each col
    for (int j = 0; j < 9; j++) {
      // add all the boxes
      if (i % 3 == 0 && j % 3 == 0) {  // we need to get the right position
        if (!isAllDiff(getBox(a, i, j))) return false;
      }
    }
  }
  return true;
}
bool Checker::checkOverlap(Puzzle* p) {
  // make sure that all the constraints have been satisfied
  vector<vector<Tile*>> a = p->getPuzzleArr();
  for (int i = 0; i < 9; i++) {
    // for each row
    if (!isAllDiff(getCol(a, 0, i))) return false;
    if (!isAllDiff(getCol(a, 3, i + 3))) return false;
    if (!isAllDiff(getCol(a, 6, i + 6))) return false;
    if (!isAllDiff(getRow(a, i, 0))) return false;
    if (!isAllDiff(getRow(a, i + 3, 3))) return false;
    if (!isAllDiff(getRow(a, i + 6, 6))) return false;

    // for each col
    for (int j = 0; j < 9; j++) {
      // add all the boxes
      if (i % 3 == 0 && j % 3 == 0) {  // we need to get the right position
        if (!isAllDiff(getBox(a, i, j))) return false;
      }
    }
  }
  // remaining boxes
  if (!isAllDiff(getBox(a, 3, 9))) return false;
  if (!isAllDiff(getBox(a, 6, 9))) return false;
  if (!isAllDiff(getBox(a, 9, 9))) return false;
  if (!isAllDiff(getBox(a, 12, 9))) return false;
  if (!isAllDiff(getBox(a, 9, 3))) return false;
  if (!isAllDiff(getBox(a, 9, 6))) return false;
  if (!isAllDiff(getBox(a, 6, 12))) return false;
  if (!isAllDiff(getBox(a, 9, 12))) return false;
  if (!isAllDiff(getBox(a, 12, 12))) return false;
  if (!isAllDiff(getBox(a, 12, 6))) return false;

  return true;
}

vector<Tile*> Checker::getBox(vector<vector<Tile*>> pArr, int x, int y) {
  vector<Tile*> arr;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      arr.push_back(pArr[x + i][y + j]);
    }
  }
  return arr;
}

vector<Tile*> Checker::getCol(vector<vector<Tile*>> pArr, int x, int y) {
  vector<Tile*> arr;
  for (int i = 0; i < 9; i++) {
    arr.push_back(pArr[x + 1][y]);
  }
  return arr;
}
vector<Tile*> Checker::getRow(vector<vector<Tile*>> pArr, int x, int y) {
  vector<Tile*> arr;
  for (int i = 0; i < 9; i++) {
    arr.push_back(pArr[x][y + i]);
  }
  return arr;
}

bool Checker::isAllDiff(vector<Tile*> x) {
  vector<int> unique;
  for (Tile* t : x) {
    for (int a : unique) {
      if (t->getNum() == a) return false;
    }
    unique.push_back(t->getNum());
  }
  return true;
}
