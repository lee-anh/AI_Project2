#include "Puzzle.h"

Puzzle::Puzzle(string filename, puzzleType type) {
  this->type = type;
  if (type == STANDARD) {
    readInStandard(filename);
    addConstraintsStandard();
  }
}

void Puzzle::printConstraintsMap() {
  map<string, vector<Constraint*>>::iterator it;
  for (it = constraints.begin(); it != constraints.end(); it++) {
    cout << "Key: " << it->first << " Values: ";
    for (int i = 0; i < it->second.size(); i++) {
      cout << ((BinaryArc*)it->second.at(i))->getTile2()->getId() << " ";
    }
    cout << endl;
  }
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

map<string, vector<Constraint*>> Puzzle::getConstraintMap() {
  return constraints;
}

bool Puzzle::ac3() {
  queue<BinaryArc*> q;  // add all the arcs to the queue
  map<string, vector<Constraint*>>::iterator it;
  for (it = constraints.begin(); it != constraints.end(); it++) {
    for (int i = 0; i < it->second.size(); i++) {
      q.push(((BinaryArc*)it->second.at(i)));
    }
  }

  while (!q.empty()) {
    BinaryArc* a = q.front();
    q.pop();
    if (a->revise()) {
      if (a->getTile1()->getDomainSize() == 0) return false;
      // for each Xk in Xi.Neighbors - Xj, do add (Xk, Xi) to queue
      vector<Constraint*> neighbors = constraints.find(a->getTile1()->getId())->second;
      for (Constraint* c : neighbors) {
        BinaryArc* b = (BinaryArc*)c;  // hopefully everything should be ok with the casting
        if (b->getTile2()->getId() != a->getTile2()->getId()) {
          q.push(b);
        }
      }
    }
  }
  return true;
}

Tile* Puzzle::getTile(int x, int y) {
  return arr[x][y];
}

// hmm we could get circular includes, but we must try it out first
void Puzzle::addConstraintsStandard() {
  vector<Alldiff*> alldiffs;

  // we need to think on the alldiff level as well. what are we going to do for forward checking?

  // add all col constraints
  for (int i = 0; i < (int)arr.size(); i++) {
    // add all cols

    alldiffs.push_back(new Alldiff(arr, COL, 0, i));
    // add all rows

    alldiffs.push_back(new Alldiff(arr, ROW, i, 0));

    for (int j = 0; j < (int)arr[i].size(); j++) {
      // add all the boxes
      if (i % 3 == 0 && j % 3 == 0) {  // we need to get the right position
        alldiffs.push_back(new Alldiff(arr, BOX, i, j));
      }
    }
  }
  cout << "num alldiffs: " << alldiffs.size() << " should be 27" << endl;

  // oh I hope this works 🙏🏼
  // convert them all to binaries
  for (int i = 0; i < (int)alldiffs.size(); i++) {
    vector<pair<string, BinaryArc*>> toAdd = alldiffs[i]->toBinaryArcs();
    for (int j = 0; j < (int)toAdd.size(); j++) {
      addToMap(toAdd[j]);  // add all the constraints to the map s
    }
  }
}

void Puzzle::addToMap(pair<string, BinaryArc*> toAdd) {
  map<string, vector<Constraint*>>::iterator it = constraints.find(toAdd.first);
  if (it != constraints.end()) {
    it->second.push_back(toAdd.second);
    return;
  }
  // add the key to the map
  vector<Constraint*> temp;
  temp.push_back(toAdd.second);
  constraints.insert(make_pair(toAdd.first, temp));
}

void Puzzle::readInStandard(string filename) {
  ifstream myFile;
  myFile.open(filename);
  if (!myFile) {
    cerr << "Could not find filename" << endl;
    return;
  }

  for (int i = 0; i < 9; i++) {
    string line;
    getline(myFile, line);
    stringstream lineStream(line);
    vector<Tile*> inner;
    for (int j = 0; j < 9; j++) {
      int assignment;
      lineStream >> assignment;
      Tile* t = new Tile(assignment, i, j);

      inner.push_back(t);
    }
    this->arr.push_back(inner);
  }
  myFile.close();
}
