#include "Control.h"

Control::Control(string filename, puzzleType type, bool useAc3, bool useMinRemainingValues, bool useLeastConstrainingValue, bool useForwardChecking) {
  this->type = type;
  this->useMinRemainingValues = useMinRemainingValues;
  this->useLeastConstrainingValue = useLeastConstrainingValue;
  this->useForwardChecking = useForwardChecking;
  backtrackCalled = 0;

  if (type == STANDARD) {
    readInStandard(filename, 9);
    constraints = new CSP(puzzle);
    constraints->addConstraintsStandard();
    constraints->printMap();
    puzzle->printPuzzle();
    if (useAc3) {
      ac3();
      puzzle->printPuzzle();
    }
    backtrackingSearch();
    printPuzzleData();
  } else if (type == OVERLAP) {
    readInStandard(filename, 15);
    constraints = new CSP(puzzle);
    constraints->addConstraintsOverlap();
    if (useAc3) {
      ac3();
      // printPuzzle();
    }
    backtrackingSearch();
    printPuzzleData();
  } else if (type == KILLER) {
    readInKiller(filename);
    constraints = new CSP(puzzle);
    puzzle->printPuzzle();
    if (useAc3) {
      ac3();
      // printPuzzle();
    }
    cout << "before add SumConstraints to Map" << endl;
    constraints->addSumConstraintsToMap(sumConstraints);
    cout << "after add SumConstraints to Map" << endl;

    backtrackingSearch();
    // now we can use the sums
    puzzle->printPuzzle();
  }
}

void Control::printPuzzleData() {
  cout << "# unassigned initially: " << puzzle->getInitialNumUnassigned() << endl;
  cout << "# times backtrack called: " << backtrackCalled << endl;
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

void Control::readInKiller(string filename) {
  ifstream myFile;
  myFile.open(filename);
  if (!myFile) {
    cerr << "Could not find filename" << endl;
    return;
  }

  for (int a = 0; a < 2; a++) {
    vector<vector<Tile*>> outer;
    for (int i = 0; i < 9; i++) {
      string line;
      getline(myFile, line);
      stringstream lineStream(line);
      vector<Tile*> inner;
      for (int j = 0; j < 9; j++) {
        int assignment = 0;
        lineStream >> assignment;
        Tile* t = new Tile(assignment, i, j);
        inner.push_back(t);
      }
      outer.push_back(inner);
    }
    if (a == 0) puzzle = new Puzzle(outer);
    if (a == 1) solution = new Puzzle(outer);
    string emptyLine;
    getline(myFile, emptyLine);
  }

  // now time to read in the sum constraints
  string sumLine;
  while (getline(myFile, sumLine)) {
    int tileNum;
    stringstream lineStream(sumLine);
    vector<int> tiles;
    while (lineStream >> tileNum) {
      tiles.push_back(tileNum);
    }
    sumConstraints.push_back(createSumHelper(tiles));
  }

  myFile.close();
}

bool Control::ac3() {
  queue<Constraint*> q;  // add all the arcs to the queue
  map<string, vector<Constraint*>> constraintMap = constraints->getMap();
  map<string, vector<Constraint*>>::iterator it;

  for (it = constraintMap.begin(); it != constraintMap.end(); it++) {
    for (int i = 0; i < it->second.size(); i++) {
      q.push(it->second.at(i));
    }
  }

  while (!q.empty()) {
    Constraint* a = q.front();
    q.pop();
    if (a->revise()) {
      if (puzzle->getTile(a->getTile1())->getDomainSize() == 0) return false;
      // for each Xk in Xi.Neighbors - Xj, do add (Xk, Xi) to queue
      vector<Constraint*> neighbors = constraintMap.find(puzzle->getTile(a->getTile1())->getId())->second;
      for (Constraint* c : neighbors) {
        // BinaryArc* b = (BinaryArc*)c;  // hopefully everything should be ok with the casting
        if (puzzle->getTile(c->getTile2())->getId() != puzzle->getTile(a->getTile2())->getId()) {
          q.push(c);
        }
      }
    }
  }

  return true;
}

void Control::backtrackingSearch() {
  backtrack();
}

bool Control::backtrack() {
  // cout << "backtrack   ";
  backtrackCalled++;
  if (puzzle->isAssignmentComplete()) {
    puzzle->printPuzzle();
    return true;
  }

  Tile* var = selectUnassignedVariable();
  // cout << "tile: " << var->getId();

  vector<int> domainValues = orderDomainValues(var);
  // cout << "|" << domainValues.size() << "|";

  for (int x : domainValues) {
    // if value is consistent with assignment then add {var = value to the assignment}

    if (checkConsistent(var->getId(), x)) {
      // cout << "   consistent x: " << x << endl;
      assignmentHistory.push(var->getDomain());  // add to memory
                                                 //  cout << "var id: " << var->getId() << " " << var->getDomain().size() << endl;
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
      var->restoreDomain(assignmentHistory.top());
      // cout << endl
      //       << "restore var id: " << assignmentHistory.top().first << " " << assignmentHistory.top().second.size() << endl;
      assignmentHistory.pop();
    }
  }

  return false;
}

Tile* Control::selectUnassignedVariable() {
  vector<Tile*> unassigned = getUnassignedVariables();
  if (unassigned.size() > 0) {
    return unassigned[0];
  }
  return nullptr;
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
  // cout << "# unassigned variables: " << toReturn.size() << "    ";
  return toReturn;
}

vector<int> Control::orderDomainValues(Tile* t) {
  // we have to look up the constraint
  if (!useLeastConstrainingValue) return t->getDomain();
  vector<int> toReturn;

  vector<Constraint*> neighbors = constraints->findConstraints(t->getId());
  vector<pair<int, int>> toSort;
  for (int x : t->getDomain()) {
    int count = 0;
    for (Constraint* c : neighbors) {
      // count up how many domains it would change, do the ordering here
      // TODO: change for sum constraints

      //  BinaryArc* b = (BinaryArc*)c;
      // willChangeDomainOfOtherTiles
      if (c->willChangeDomainOfOtherTiles(t->getId(), x)) count++;
      // if (b->getTile2()->isInDomain(x)) count++;
    }
    toSort.push_back(make_pair(count, x));
  }
  sort(toSort.begin(), toSort.end());

  for (pair<int, int> val : toSort) {
    toReturn.push_back(val.second);
  }

  return toReturn;
}

// the purpose of forwardCheck is to whittle down the domains
vector<vector<pair<Tile*, vector<int>>>> Control::forwardCheck(Tile* t) {
  vector<Constraint*> neighbors = constraints->findConstraints(t->getId());
  vector<vector<pair<Tile*, vector<int>>>> history;
  //  cout << "check for " << t->getId() << " " << t->getNum() << " | ";
  for (Constraint* c : neighbors) {
    // TODO: we need to make this work for the sums too
    // why does this only sometimes work?
    // BinaryArc* b = (BinaryArc*)c;
    //  cout << "id1: " << b->getId1() << " id2: " << b->getId2() << endl;
    // cout << "check: " << b->getTile1()->getId() << " check: " << b->getTile2()->getId() << endl;
    // Tile* n = b->getTile2();
    // TODO: removeFromDomainOfOtherTiles
    history.push_back(c->removeFromDomainOfOtherTiles(t->getId(), t->getNum()));

    /*
    if (n->getNum() == 0) {  // unassigned
      // cout << n->getId() << " ";

      //  history.push_back(make_pair(string(n->getId()), vector<int>(n->getDomain())));
      history.push_back(make_pair(n, n->getDomain()));

      n->removeFromDomain(t->getNum());

      if (n->getDomainSize() == 0) {  // technically we wouldn't reach this point?
        // restoreNeighborsForForwardCheck(history);
        inferenceHistory.push(history);
        return history;
      }
    }
    */
  }
  //  cout << endl;

  // add to history of changes
  inferenceHistory.push(history);
  return history;
}

// restore from forward check?
void Control::restoreNeighborsForForwardCheck(vector<vector<pair<Tile*, vector<int>>>> history) {
  // cout << endl
  //     << "restore: ";

  for (vector<pair<Tile*, vector<int>>> toRestore : history) {
    for (pair<Tile*, vector<int>> x : toRestore) {
      Tile* tile = x.first;
      //  cout << toRestore.first->getId() << " = " << tile->getId() << " ";
      tile->restoreDomain(x.second);
    }
  }
  // cout << endl;
}

bool Control::checkConsistent(string tileId, int proposedAssignment) {
  //  cout << "begin checkConsistent" << endl;
  // cout << "tileId: " << tileId << endl;
  vector<Constraint*> neighbors = constraints->findConstraints(tileId);
  // cout << "after find constraints" << endl;
  for (Constraint* c : neighbors) {
    // TODO: make this work for sum constraint too
    // we have to check it with the currently assigned things
    //  BinaryArc* b = (BinaryArc*)c;
    //   Tile* n = b->getTile2();

    // if ((n->getNum() != 0) && (proposedAssignment == n->getNum())) return false;
    // if (!((BinaryArc*)c)->proposeAssignment(proposedAssignment)) return false;
    if (!(c->proposeAssignment(tileId, proposedAssignment))) return false;
  }
  return true;
}

Sum* Control::createSumHelper(vector<int> tiles) {
  int runningSum = 0;
  vector<Tile*> toPass;
  for (int x : tiles) {
    int row = x / 9;
    int col = x % 9;
    toPass.push_back(puzzle->getTile(row, col));
    runningSum += solution->getTile(row, col)->getNum();
  }
  cout << "total sum: " << runningSum << endl;
  return new Sum(runningSum, toPass);
}