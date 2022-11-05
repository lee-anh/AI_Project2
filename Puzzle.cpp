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
  // if (arr.size() == 9) {
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      if (arr[i][j]->getNum() == 0) return false;
    }
  }
  //  }

  /*
  else if (arr.size() == 15) {
    // for overlapping we will get some empty tiles
    int count = 0;
    for (int i = 0; i < (int)arr.size(); i++) {
      for (int j = 0; j < (int)arr[i].size(); j++) {
        if (arr[i][j]->getNum() == 0) count++;
      }
    }
    if (count != 54) return false;
  }
  */

  // puzzle length

  return true;
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
Tile* Puzzle::getTile(string id) {
  //  cout << "before getTile" << endl;
  int x = 0;
  int y = 0;
  if (id.length() == 3) {
    x = stoi(string(1, id[0]));
    y = stoi(string(1, id[2]));
  } else if (id.length() == 5) {
    x = stoi(string(2, id[0]));
    y = stoi(string(2, id[3]));
  } else {
    int space = 0;
    for (int i = 0; i < (int)id.length(); i++) {
      if (id[i] == '-') {
        space = i;
        break;
      }
    }

    if (space == 2) {
      x = stoi(string(2, id[0]));
      y = stoi(string(1, id[3]));
    } else {
      x = stoi(string(1, id[0]));
      y = stoi(string(2, id[2]));
    }
  }
  //  cout << "end of getTile" << endl;
  return getTile(x, y);
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
