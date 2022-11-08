#include "Puzzle.h"

/// @brief Puzzle Constructor
/// @param arr array of tiles representing the board
Puzzle::Puzzle(vector<vector<Tile*>> arr) {
  this->arr = arr;
  initialNumUnassigned = numUnassigned();
}

/// @brief Deep copy constructor
/// @param p
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
  this->initialNumUnassigned = p->initialNumUnassigned;
}

/// @brief check if assignment complete
/// @return true if all the tiles have assigned values
bool Puzzle::isAssignmentComplete() {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      if (arr[i][j]->getNum() == 0) return false;
    }
  }
  return true;
}

/// @brief get the number of tiles that were initially unassigned
/// @return
int Puzzle::getInitialNumUnassigned() {
  return initialNumUnassigned;
}

/// @brief get the current number of tiles that are unassigned
/// @return the current number of unassigned tiles
int Puzzle::numUnassigned() {
  int count = 0;
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      if (arr[i][j]->getNum() == 0) count++;
    }
  }
  return count;
}

/// @brief get the average domain size of unassigned tiles
/// @return the average number of elements in the domain
float Puzzle::getAverageDomainSize() {
  long long total = 0;
  int count = 0;
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      if (arr[i][j]->getNum() == 0 && arr[i][j]->getNum() != -1) {
        total += arr[i][j]->getDomainSize();
        count++;
      }
    }
  }
  if (count == 0) return 0;

  return total * 1.0 / count;
}

/// @brief get a tile given x and y coordinate
/// @param x coordinate
/// @param y coordinate
/// @return Tile object
Tile* Puzzle::getTile(int x, int y) {
  return arr[x][y];
}

/// @brief get a tile given x and y coordinate in a pair
/// @param coordinate
/// @return Tile object
Tile* Puzzle::getTile(pair<int, int> coordinate) {
  return arr[coordinate.first][coordinate.second];
}

/// @brief get the underlying array of Tiles
/// @return
vector<vector<Tile*>> Puzzle::getPuzzleArr() {
  return arr;
}

/// @brief print the data of each Tile in the puzzle
void Puzzle::printPuzzle() {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      int num = arr[i][j]->getNum();
      if (num == 0 || num == -1) {
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
      if (arr.size() == 9) cout << "----------------------" << endl;
      if (arr.size() == 15) cout << "-------------------------------------" << endl;
    }
  }
  cout << endl;
}

void Puzzle::printPuzzleData() {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      arr[i][j]->printTile();
    }
  }
}
