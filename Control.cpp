#include "Control.h"

Control::Control(string filename, puzzleType type) {
  this->type = type;
  if (type == STANDARD) {
    readInStandard(filename);
    addConstraintsStandard();
  }
}

void Control::printConstraintsMap() {
  map<string, vector<Constraint*>>::iterator it;
  for (it = constraints.begin(); it != constraints.end(); it++) {
    cout << "Key: " << it->first << " Values: ";
    for (int i = 0; i < it->second.size(); i++) {
      // cout << ((BinaryArc*)it->second.at(i))->getTile2()->getId() << " ";
      cout << ((BinaryArc*)it->second.at(i))->getId2() << " ";
    }
    cout << endl;
  }
}

void Control::printPuzzle() {
  root->getPuzzle()->printPuzzle();
}

bool Control::ac3() {
  Puzzle* rootPuzzle = root->getPuzzle();
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
    if (revise(a)) {
      Tile* t1 = rootPuzzle->getTile(a->getId1());
      //  Tile* t2 = rootPuzzle->getTile(a->getId2());
      if (t1->getDomainSize() == 0) return false;
      // for each Xk in Xi.Neighbors - Xj, do add (Xk, Xi) to queue
      vector<Constraint*> neighbors = constraints.find(a->getId1())->second;
      for (Constraint* c : neighbors) {
        BinaryArc* b = (BinaryArc*)c;  // hopefully everything should be ok with the casting
        if (b->getId2() != a->getId2()) {
          q.push(b);
        }
      }
    }
  }

  return true;
}

// revise is called for a specific Binary Constraint
bool Control::revise(BinaryArc* ba) {
  // cout << "revised called" << endl;
  bool revised = false;
  Puzzle* p = root->getPuzzle();
  Tile* t1 = p->getTile(ba->getId1());
  Tile* t2 = p->getTile(ba->getId2());

  vector<int> domain1 = t1->getDomain();
  vector<int> domain2 = t2->getDomain();

  for (int x : domain1) {
    int noAllowCount = 0;

    for (int y : domain2) {  // really only triggers when we already have an assignment
      if (x == y) {
        noAllowCount++;
      }
    }

    if (noAllowCount == (int)domain2.size()) {  // no value y in domain 2 allows (x, y) to satisfy NE
      t1->removeFromDomain(x);
      revised = true;
    }
  }

  return revised;
}

void Control::addConstraintsStandard() {
  vector<Alldiff*> alldiffs;

  // we need to think on the alldiff level as well. what are we going to do for forward checking?
  vector<vector<Tile*>> arr = root->getPuzzle()->getPuzzleArr();
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
      addToMap(toAdd[j]);  // add all the constraints to the map
    }
  }
}

void Control::addToMap(pair<string, BinaryArc*> toAdd) {
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

void Control::readInStandard(string filename) {
  ifstream myFile;
  myFile.open(filename);
  if (!myFile) {
    cerr << "Could not find filename" << endl;
    return;
  }

  vector<vector<Tile*>> outer;
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
    outer.push_back(inner);
  }
  Puzzle* rootPuzzle = new Puzzle(outer);
  root = new PuzzleNode(rootPuzzle);
  myFile.close();
}
