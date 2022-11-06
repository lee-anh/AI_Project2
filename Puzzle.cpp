#include "Puzzle.h"

Puzzle::Puzzle(vector<vector<Tile*>> arr) {
  this->arr = arr;
  initialNumUnassigned = numUnassigned();
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
  this->initialNumUnassigned = p->initialNumUnassigned;
}

bool Puzzle::isAssignmentComplete() {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      if (arr[i][j]->getNum() == 0) return false;
    }
  }
  return true;
}

int Puzzle::getInitialNumUnassigned() {
  return initialNumUnassigned;
}
int Puzzle::numUnassigned() {
  int count = 0;
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      if (arr[i][j]->getNum() == 0) count++;
    }
  }
  return count;
}

void Puzzle::assignDomainOnes() {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      if (arr[i][j]->getDomainSize() == 1) {
        arr[i][j]->setNum(arr[i][j]->getDomain().at(0));
      }
    }
  }
}

Tile* Puzzle::getTile(int x, int y) {
  return arr[x][y];
}

vector<vector<Tile*>> Puzzle::getPuzzleArr() {
  return arr;
}

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
}

void Puzzle::printPuzzleData() {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      arr[i][j]->printTile();
    }
  }
}
