#include "Puzzle.h"

Puzzle::Puzzle(vector<vector<Tile*>> arr) {
  this->arr = arr;
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

Tile* Puzzle::getTile(int x, int y) {
  return arr[x][y];
}
Tile* Puzzle::getTile(string id) {
  // the problem is literally here and it's easy

  int x = stoi(string(1, id[0]));
  int y = stoi(string(1, id[1]));
  // cout << "x: " << x << " y: " << y << endl;

  return getTile(x, y);
}