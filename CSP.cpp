#include "CSP.h"

/// @brief CSP constructor
/// @param puzzle to create map for
CSP::CSP(Puzzle* puzzle) {
  this->puzzle = puzzle;
}

/// @brief get the underlying map
/// @return
map<string, vector<Constraint*>> CSP::getMap() {
  return constraints;
}

/// @brief get all the constraints (value) given a tileId (key)
/// @param tileId the id of the tile to find the constraints of
/// @return the value (vector of Constraints)
vector<Constraint*> CSP::findConstraints(string tileId) {
  return constraints.find(tileId)->second;
}

/// @brief add Alldiff constraints for a Standard puzzle to the map
/// convert them all to BinaryArcs
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
    vector<pair<string, BinaryArc*>> toAdd = alldiffs[i]->toBinaryArcs();
    for (int j = 0; j < (int)toAdd.size(); j++) {
      addBinaryArcToMap(toAdd[j]);  // add all the constraints to the map
    }
  }
}

/// @brief add Alldiff constraints for a Overlapping puzzle to the map
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
    vector<pair<string, BinaryArc*>> toAdd = alldiffs[i]->toBinaryArcs();
    for (int j = 0; j < (int)toAdd.size(); j++) {
      addBinaryArcToMap(toAdd[j]);  // add all the constraints to the map
    }
  }
}

/// @brief add a BinaryArc to the map
/// @param toAdd a pair of a tileid and a binary arc to add
void CSP::addBinaryArcToMap(pair<string, BinaryArc*> toAdd) {
  map<string, vector<Constraint*>>::iterator it = constraints.find(toAdd.first);
  if (it != constraints.end()) {
    for (Constraint* c : it->second) {
      if ((c->getTiles().at(0)->getId() == toAdd.second->getTiles().at(0)->getId()) && (c->getTiles().at(1)->getId() == toAdd.second->getTiles().at(1)->getId())) {
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

/// @brief add a vector of Sum to the map
/// @param sums a vector of Sums to add
void CSP::addSumConstraintsToMap(vector<Sum*> sums) {
  for (Sum* s : sums) {
    // cout << "s size " << s->getTiles().size() << endl;
    for (Tile* t : s->getTiles()) {
      addSumToMap(make_pair(t->getId(), s));
    }
  }
}

/// @brief print the constraints in the map
void CSP::printMap() {
  map<string, vector<Constraint*>>::iterator it;
  for (it = constraints.begin(); it != constraints.end(); it++) {
    cout << "Key: " << it->first << " Values: ";
    for (int i = 0; i < it->second.size(); i++) {
      cout << "( ";
      for (Tile* t : it->second.at(i)->getTiles()) {
        cout << t->getId() << " ";
      }
      cout << ")";
      //  cout << ((BinaryArc*)it->second.at(i))->getTile2()->getId() << " ";
      // cout << (puzzle->getTile(it->second.at(i)->getTile2()))->getId() << " ";
    }
    cout << endl;
  }
}

/// @brief add one sum constraint to the map
/// @param toAdd a pair of tile id and Sum Constraint to add
void CSP::addSumToMap(pair<string, Sum*> toAdd) {
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