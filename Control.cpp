#include "Control.h"

Control::Control(string filename, puzzleType type, bool useAc3, bool useMinRemainingValues, bool useLeastConstrainingValue, bool useForwardChecking) {
  this->type = type;
  this->useMinRemainingValues = useMinRemainingValues;
  this->useLeastConstrainingValue = useLeastConstrainingValue;
  this->useForwardChecking = useForwardChecking;

  if (type == STANDARD) {
    readInStandard(filename, 9);
    addConstraintsStandard();
    printPuzzle();
    if (useAc3) {
      ac3();
    }
  } else if (type == OVERLAP) {
    readInStandard(filename, 15);
    addConstraintsOverlap();
    printPuzzle();
    if (useAc3) {
      ac3();
      printPuzzle();
    }
  }
}

void Control::printConstraintsMap() {
  map<string, vector<Constraint*>>::iterator it;
  for (it = constraints.begin(); it != constraints.end(); it++) {
    // cout << "Key: " << it->first << " Values: ";
    for (int i = 0; i < it->second.size(); i++) {
      // cout << ((BinaryArc*)it->second.at(i))->getTile2()->getId() << " ";
      // cout << ((BinaryArc*)it->second.at(i))->getId2() << " ";
    }
    // cout << endl;
  }
}

void Control::printPuzzle() {
  puzzle->printPuzzle();
  cout << endl;
}

void Control::addConstraintsStandard() {
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
      addToMap(toAdd[j]);  // add all the constraints to the map
    }
  }
}

void Control::addConstraintsOverlap() {
  vector<Alldiff*> alldiffs;

  // we need to think on the alldiff level as well. what are we going to do for forward checking?
  vector<vector<Tile*>> arr = puzzle->getPuzzleArr();
  // add all col constraints
  for (int i = 0; i < (int)9; i++) {
    // add all cols for first puzzle
    alldiffs.push_back(new Alldiff(arr, COL, 0, i));

    // add all cols for second puzzle
    alldiffs.push_back(new Alldiff(arr, COL, 3, i + 3));

    // add all cols for third puzzle
    alldiffs.push_back(new Alldiff(arr, COL, 6, i + 6));

    // add all rows for first puzzle
    alldiffs.push_back(new Alldiff(arr, ROW, i, 0));

    // add all rows for second puzzle
    alldiffs.push_back(new Alldiff(arr, ROW, i + 3, 3));

    // add all rows for third  puzzle
    alldiffs.push_back(new Alldiff(arr, ROW, i + 6, 6));

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
      addToMap(toAdd[j]);  // add all the constraints to the map
    }
  }
}

void Control::addToMap(pair<string, BinaryArc*> toAdd) {
  map<string, vector<Constraint*>>::iterator it = constraints.find(toAdd.first);
  if (it != constraints.end()) {
    for (Constraint* c : it->second) {
      BinaryArc* b = (BinaryArc*)c;
      // do not allow duplicates
      if ((b->getId1() == toAdd.second->getId1()) && (b->getId2() == toAdd.second->getId2())) {
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

void Control::readInStandard(string filename, int side) {
  ifstream myFile;
  myFile.open(filename);
  if (!myFile) {
    cerr << "Could not find filename" << endl;
    return;
  }

  vector<vector<Tile*>> outer;
  for (int i = 0; i < side; i++) {
    string line;
    getline(myFile, line);
    stringstream lineStream(line);
    vector<Tile*> inner;
    for (int j = 0; j < side; j++) {
      string temp;
      lineStream >> temp;
      // lineStream >> assignment;

      int assignment = 0;
      if (temp == "-") {
        assignment = -1;
      } else {
        assignment = stoi(temp);
      }

      Tile* t = new Tile(assignment, i, j);

      inner.push_back(t);
    }
    outer.push_back(inner);
  }

  puzzle = new Puzzle(outer);

  myFile.close();
}

bool Control::ac3() {
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

// TODO: move this back to BinaryArc?

void Control::backtrackingSearch() {
  // puzzle->printPuzzleData();
  // cout << endl;
  //  cout << endl;
  backtrack();
  //  puzzle->printPuzzleData();
}

bool Control::backtrack() {
  // cout << "backtrack called" << endl;
  if (puzzle->isAssignmentComplete()) {
    puzzle->printPuzzle();
    return true;
  }

  Tile* var = selectUnassignedVariable();
  // cout << "after selectUnassignedVariable" << endl;
  vector<int> domainValues = orderDomainValues(var);
  // cout << "after orderDomainValues" << endl;
  for (int x : domainValues) {
    // if value is consistent with assignment then add {var = value to the assignment}
    // cout << "in domainValues loop" << endl;
    if (checkConsistent(var->getId(), x)) {
      assignmentHistory.push(make_pair(var->getId(), vector<int>(var->getDomain())));  // add to memory
      var->setNum(x);
      // where should we keep the stack of inferences? here or somewhere else?
      if (useForwardChecking) {
        forwardCheck(var);
        if (backtrack()) {
          return true;
        }
        restoreNeighborsForForwardCheck(inferenceHistory.top());
        inferenceHistory.pop();
      } else {
        if (backtrack()) return true;
      }
      var->restoreDomain(vector<int>(assignmentHistory.top().second));
      assignmentHistory.pop();
    }
  }

  return false;
}

Tile* Control::selectUnassignedVariable() {
  // thinking recursively so hopefully this works?
  // TODO: should this go outside? otherwise we are always looking at the same ones?

  vector<Tile*> unassigned = getUnassignedVariables();

  if (unassigned.size() > 0) {
    return unassigned[0];  // just return the first one right?
  }
  // cout << "size is 0" << endl;
  return nullptr;  // will this work?
}

vector<Tile*> Control::getUnassignedVariables() {
  vector<vector<Tile*>> arr = puzzle->getPuzzleArr();

  // otherwise just consider the tiles in order
  vector<Tile*> toReturn;
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      // we only want the unassigned tiles - and not from certain regions for the overlapping puzzle!
      if (arr[i][j]->getNum() == 0) toReturn.push_back(arr[i][j]);
    }
  }

  if (useMinRemainingValues) {
    // sort the array to return by domain size, ascending
    sort(toReturn.begin(), toReturn.end(), tileLessThan());
  }
  return toReturn;
}

vector<int> Control::orderDomainValues(Tile* t) {
  // we have to look up the constraint
  if (!useLeastConstrainingValue) return t->getDomain();
  vector<int> toReturn;

  vector<Constraint*> neighbors = constraints.find(t->getId())->second;
  // more efficient way to do this
  for (Constraint* c : neighbors) {
    // count up how many domains it would change, do the ordering here
    // TODO: do this
    BinaryArc* b = (BinaryArc*)c;
  }
  return toReturn;
}

// the purpose of forwardCheck is to whittle down the domains
vector<pair<string, vector<int>>> Control::forwardCheck(Tile* t) {
  vector<Constraint*> neighbors = constraints.find(t->getId())->second;
  vector<pair<string, vector<int>>> history;

  for (Constraint* c : neighbors) {
    // TODO: we need to make this work for the sums too
    // why does this only sometimes work?
    BinaryArc* b = (BinaryArc*)c;
    Tile* n = b->getTile2();
    if (n->getNum() == 0) {  // unassigned
      history.push_back(make_pair(n->getId(), vector<int>(n->getDomain())));

      n->removeFromDomain(t->getNum());
      // we never really reach this
      if (n->getDomainSize() == 0) {  // technically we wouldn't reach this point?
        // restoreNeighborsForForwardCheck(history);
        inferenceHistory.push(history);
        return history;
      }
    }
  }

  // add to history of changes
  inferenceHistory.push(history);
  return history;
}

// restore from forward check?
void Control::restoreNeighborsForForwardCheck(vector<pair<string, vector<int>>> history) {
  // cout << "restore called" << endl;
  for (pair<string, vector<int>> toRestore : history) {
    Tile* tile = puzzle->getTile(toRestore.first);
    tile->restoreDomain(vector<int>(toRestore.second));
  }
}

bool Control::isArcConsistent(BinaryArc* ba, int proposedAssignment) {
  Tile* t2 = puzzle->getTile(ba->getId2());

  int allowed = 0;
  for (int x : t2->getDomain()) {
    if (proposedAssignment != x) allowed++;
  }

  if (allowed == 0) {
    // cout << "is not arc consistent" << endl;
    return false;
  }
  return true;
}

bool Control::checkConsistent(string tileId, int proposedAssignment) {
  // cout << "begin checkConsistent" << endl;
  // cout << "tileId: " << tileId << endl;
  vector<Constraint*> neighbors = constraints.find(tileId)->second;
  // cout << "after find constraints" << endl;
  for (Constraint* c : neighbors) {
    // TODO: make this work for sum constraint too
    // we have to check it with the currently assigned things
    BinaryArc* b = (BinaryArc*)c;
    Tile* n = b->getTile2();

    // if ((n->getNum() != 0) && (proposedAssignment == n->getNum())) return false;
    if (!isArcConsistent((BinaryArc*)c, proposedAssignment)) {
      return false;
    }
  }
  return true;
}
