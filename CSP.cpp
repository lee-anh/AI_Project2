#include "CSP.h"

CSP::CSP(Puzzle* puzzle) {
  this->puzzle = puzzle;
}
map<string, vector<Constraint*>> CSP::getMap() {
  return constraints;
}
vector<Constraint*> CSP::findConstraints(string tileId) {
  return constraints.find(tileId)->second;
}

void CSP::addConstraintsStandard() {
  vector<Alldiff*> alldiffs;

  // we need to think on the alldiff level as well. what are we going to do for forward checking?
  vector<vector<Tile*>> arr = puzzle->getPuzzleArr();
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
  // cout << "num alldiffs: " << alldiffs.size() << " should be 27" << endl;

  // convert them all to binaries
  for (int i = 0; i < (int)alldiffs.size(); i++) {
    vector<pair<string, Constraint*>> toAdd = alldiffs[i]->toBinaryArcs();
    for (int j = 0; j < (int)toAdd.size(); j++) {
      addBinaryArcToMap(toAdd[j]);  // add all the constraints to the map
    }
  }
}

void CSP::addConstraintsOverlap() {
  vector<Alldiff*> alldiffs;

  // we need to think on the alldiff level as well. what are we going to do for forward checking?
  vector<vector<Tile*>> arr = puzzle->getPuzzleArr();
  // add all col constraints
  for (int i = 0; i < 9; i++) {
    // add all cols
    alldiffs.push_back(new Alldiff(arr, COL, 0, i));      // first
    alldiffs.push_back(new Alldiff(arr, COL, 3, i + 3));  // second
    alldiffs.push_back(new Alldiff(arr, COL, 6, i + 6));  // third

    // add all rows
    alldiffs.push_back(new Alldiff(arr, ROW, i, 0));      // first
    alldiffs.push_back(new Alldiff(arr, ROW, i + 3, 3));  // second
    alldiffs.push_back(new Alldiff(arr, ROW, i + 6, 6));  // third

    for (int j = 0; j < (int)9; j++) {
      // add all the boxes
      if (i % 3 == 0 && j % 3 == 0) {  // we need to get the right position
        alldiffs.push_back(new Alldiff(arr, BOX, i, j));
      }
    }
  }

  // add the remaining boxes
  alldiffs.push_back(new Alldiff(arr, BOX, 3, 9));
  alldiffs.push_back(new Alldiff(arr, BOX, 6, 9));
  alldiffs.push_back(new Alldiff(arr, BOX, 9, 9));
  alldiffs.push_back(new Alldiff(arr, BOX, 12, 9));
  alldiffs.push_back(new Alldiff(arr, BOX, 9, 3));
  alldiffs.push_back(new Alldiff(arr, BOX, 9, 6));
  alldiffs.push_back(new Alldiff(arr, BOX, 6, 12));
  alldiffs.push_back(new Alldiff(arr, BOX, 9, 12));
  alldiffs.push_back(new Alldiff(arr, BOX, 12, 12));
  alldiffs.push_back(new Alldiff(arr, BOX, 12, 6));

  // convert them all to binaries
  for (int i = 0; i < (int)alldiffs.size(); i++) {
    vector<pair<string, Constraint*>> toAdd = alldiffs[i]->toBinaryArcs();
    for (int j = 0; j < (int)toAdd.size(); j++) {
      addBinaryArcToMap(toAdd[j]);  // add all the constraints to the map
    }
  }
}

void CSP::addBinaryArcToMap(pair<string, Constraint*> toAdd) {
  map<string, vector<Constraint*>>::iterator it = constraints.find(toAdd.first);
  if (it != constraints.end()) {
    // TODO: put this back in

    for (Constraint* c : it->second) {
      //  BinaryArc* b = (BinaryArc*)c;
      // do not allow duplicates
      // if ((b->getId1() == toAdd.second->getId1()) && (b->getId2() == toAdd.second->getId2())) {
      if ((puzzle->getTile(c->getTile1())->getId() == puzzle->getTile(toAdd.second->getTile1())->getId()) && (puzzle->getTile(c->getTile2())->getId() == puzzle->getTile(toAdd.second->getTile2())->getId())) {
        return;
      }
    }
    it->second.push_back(toAdd.second);

    return;
  }

  // add the key to the map
  vector<Constraint*> temp;
  temp.push_back(toAdd.second);
  constraints.insert(make_pair(toAdd.first, temp));
}

void CSP::addSumConstraintsToMap(vector<Constraint*> sums) {
  for (Constraint* s : sums) {
    cout << "s size " << s->getTiles().size() << endl;
    for (Tile* t : s->getTiles()) {
      addSumToMap(make_pair(t->getId(), s));
    }
  }
}

void CSP::addSumToMap(pair<string, Constraint*> toAdd) {
  map<string, vector<Constraint*>>::iterator it = constraints.find(toAdd.first);
  if (it != constraints.end()) {
    it->second.push_back(toAdd.second);
    // we are not checking for duplicates
    return;
  }
  // add the key to the map
  vector<Constraint*> temp;
  temp.push_back(toAdd.second);
  constraints.insert(make_pair(toAdd.first, temp));
}

void CSP::printMap() {
  map<string, vector<Constraint*>>::iterator it;
  for (it = constraints.begin(); it != constraints.end(); it++) {
    cout << "Key: " << it->first << " Values: ";
    for (int i = 0; i < it->second.size(); i++) {
      //  cout << ((BinaryArc*)it->second.at(i))->getTile2()->getId() << " ";
      cout << (puzzle->getTile(it->second.at(i)->getTile2()))->getId() << " ";
    }
    cout << endl;
  }
}