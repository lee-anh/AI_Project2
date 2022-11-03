#include "Puzzle.h"

Puzzle::Puzzle(vector<vector<Tile*>> arr) {
  this->arr = arr;
}

// deep copy constructor
Puzzle::Puzzle(Puzzle* p) {
  this->type = p->type;
  // deep copy the tiles
  vector<vector<Tile*>> newTilesOuter;
  for (int i = 0; i < (int)p->arr.size(); i++) {
    vector<Tile*> newTilesInner;
    for (int j = 0; j < (int)p->arr[i].size(); j++) {
      newTilesInner.push_back(new Tile(p->getTile(i, j)));
    }
    newTilesOuter.push_back(newTilesInner);
  }
  this->arr = newTilesOuter;
}

bool Puzzle::isAssignmentComplete() {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      if (arr[i][j]->getNum() == 0) return false;
    }
  }
  return true;
}

Tile* Puzzle::getTile(int x, int y) {
  return arr[x][y];
}
Tile* Puzzle::getTile(string id) {
  int x = stoi(string(1, id[0]));
  int y = stoi(string(1, id[1]));

  return getTile(x, y);
}

vector<vector<Tile*>> Puzzle::getPuzzleArr() {
  return arr;
}

void Puzzle::printPuzzle() {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      int num = arr[i][j]->getNum();
      if (num == 0) {
        cout << "  ";  // 2 spaces
      } else {
        cout << num << " ";
      }
      if ((j + 1) % 3 == 0 && j != (int)arr[i].size() - 1) {
        cout << "| ";
      }
    }
    cout << endl;
    if ((i + 1) % 3 == 0 && i != (int)arr.size() - 1) {
      cout << "----------------------" << endl;
    }
  }
}

void Puzzle::printPuzzleData() {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      arr[i][j]->printTile();
    }
  }
}
