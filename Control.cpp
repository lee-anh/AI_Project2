#include "Control.h"
/// @brief Control Constructor
/// @param filename
/// @param outputFilename
/// @param type
/// @param useAc3
/// @param useMinRemainingValues
/// @param useLeastConstrainingValue
/// @param useForwardChecking
Control::Control(string filename, string outputFilename, puzzleType type, bool useAc3, bool useMinRemainingValues, bool useLeastConstrainingValue, bool useForwardChecking) {
  this->type = type;
  this->useAc3 = useAc3;
  this->useMinRemainingValues = useMinRemainingValues;
  this->useLeastConstrainingValue = useLeastConstrainingValue;
  this->useForwardChecking = useForwardChecking;
  this->outputFilename = outputFilename;
  backtrackCalled = 0;
  numUnassignedAfterAc3 = 0;
  averageDomainSizeAfterAc3 = 0;
  depthSum = 0;
  currentDepth = 0;

  if (type == STANDARD) {
    readInStandard(filename, 9);
    constraints = new CSP(puzzle);
    constraints->addConstraintsStandard();
    // constraints->printMap();
    puzzle->printPuzzle();
    if (useAc3) {
      ac3();
      numUnassignedAfterAc3 = puzzle->numUnassigned();
      averageDomainSizeAfterAc3 = puzzle->getAverageDomainSize();
      // puzzle->printPuzzle();
    }

    backtrackingSearch();
    isSolution = Checker::checkStandard(puzzle);
    printPuzzleData();
  } else if (type == OVERLAP) {
    readInStandard(filename, 15);
    constraints = new CSP(puzzle);
    constraints->addConstraintsOverlap();
    puzzle->printPuzzle();
    if (useAc3) {
      ac3();
      numUnassignedAfterAc3 = puzzle->numUnassigned();
      averageDomainSizeAfterAc3 = puzzle->getAverageDomainSize();
      // printPuzzle();
    }
    backtrackingSearch();
    isSolution = Checker::checkOverlap(puzzle);
    printPuzzleData();
  } else if (type == KILLER) {
    readInKiller(filename);
    constraints = new CSP(puzzle);
    constraints->addConstraintsStandard();
    puzzle->printPuzzle();

    if (useAc3) {
      ac3();
      numUnassignedAfterAc3 = puzzle->numUnassigned();
      averageDomainSizeAfterAc3 = puzzle->getAverageDomainSize();
      // printPuzzle();
    }
    // constraints->printMap();
    // cout << "before add SumConstraints to Map" << endl;
    constraints->addSumConstraintsToMap(sumConstraints);
    // cout << "after add SumConstraints to Map" << endl;
    //  constraints->printMap();
    backtrackingSearch();
    isSolution = Checker::checkKiller(puzzle, solution);
    printPuzzleData();
  }
}

/// @brief print puzzle stats to terminal
void Control::printPuzzleData() {
  cout << "# unassigned initially: " << puzzle->getInitialNumUnassigned() << endl;
  cout << "# unassigned after ac3: " << numUnassignedAfterAc3 << endl;
  cout << "average domain size after ac3: " << averageDomainSizeAfterAc3 << endl;  // branching factor
  cout << "average depth: " << depthSum * 1.0 / backtrackCalled << endl;
  //  cout << "average domain size at end: " << puzzle->getAverageDomainSize() << endl;
  cout << "# times backtrack called: " << backtrackCalled << endl;
  cout << "is solution: " << isSolution << endl;
}

/// @brief write data to log file
void Control::writeDataToLog() {
  ofstream myFile;
  myFile.open(outputFilename, ios_base::app);
  myFile << useAc3 << "\t "
         << useMinRemainingValues << "\t"
         << useLeastConstrainingValue << "\t"
         << useForwardChecking << "\t"
         << puzzle->getInitialNumUnassigned() << "\t"  // "# unassigned initially
         << numUnassignedAfterAc3 << "\t"              //# unassigned after ac3
         << averageDomainSizeAfterAc3 << "\t"          // average domain size after ac3
         << depthSum * 1.0 / backtrackCalled << "\t"   // average depth
         << backtrackCalled << "\t"                    //# times backtrack called
         << timeToSolve << "\t"                        // time to solve
         << isSolution << endl;
  myFile.close();
}

/// @brief Callee for recursive backtracking()
/// also times how long the backtrack algorithm took
void Control::backtrackingSearch() {
  auto start = chrono::high_resolution_clock::now();
  backtrack();
  auto stop = chrono::high_resolution_clock::now();
  auto duration = duration_cast<chrono::microseconds>(stop - start);
  timeToSolve = duration.count();
}

/// @brief read in a Standard or overlapping puzzle
/// @param filename
/// @param side 9 if standard, 15 if overlapping
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

/// @brief read in a killer puzzle
/// @param filename
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

// @brief AC-3 preprocessing
/// @return true if assignments were successfully made, false if we ran into a no solution scenario
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
      if (a->getTiles().at(0)->getDomainSize() == 0) return false;
      // for each Xk in Xi.Neighbors - Xj, do add (Xk, Xi) to queue
      vector<Constraint*> neighbors = constraintMap.find(a->getTiles().at(0)->getId())->second;
      for (Constraint* c : neighbors) {
        // BinaryArc* b = (BinaryArc*)c;  // hopefully everything should be ok with the casting
        if (c->getTiles().at(1)->getId() != a->getTiles().at(1)->getId()) {
          q.push(c);
        }
      }
    }
  }

  return true;
}

/// @brief recursive backtrack
/// @return
bool Control::backtrack() {
  currentDepth++;
  backtrackCalled++;
  if (puzzle->isAssignmentComplete()) {
    puzzle->printPuzzle();
    if (type == STANDARD) {
      if (Checker::checkStandard(puzzle)) return true;
    } else if (type == OVERLAP) {
      if (Checker::checkOverlap(puzzle)) return true;
    } else {
      if (Checker::checkKiller(puzzle, solution)) return true;
    }
    return false;
  }

  Tile* var = selectUnassignedVariable();

  vector<int> domainValues = orderDomainValues(var);
  //   cout << "|" << domainValues.size() << "|";

  // cout << "tile: " << var->getId() << " ";
  // for (int x : domainValues) {
  //   cout << " " << x;
  // }
  // cout << endl;

  for (int x : domainValues) {
    // if value is consistent with assignment then add {var = value to the assignment}

    // cout << "tile: " << var->getId();
    if (checkConsistent(var->getId(), x)) {
      // cout << "   consistent x: " << x << endl;
      assignmentHistory.push(var->getDomain());  // add to memory
                                                 //  cout << "var id: " << var->getId() << " " << var->getDomain().size() << endl;
      var->setNum(x);

      if (useForwardChecking) {
        if (forwardCheck(var)) {
          if (backtrack()) {
            return true;
          }
          restoreNeighborsForForwardCheck(inferenceHistory.top());
          inferenceHistory.pop();
        } else {
          //   cout << "forward check failed " << endl;
        }
      } else {
        if (backtrack()) return true;
      }
      var->restoreDomainNoSet(assignmentHistory.top());
      //  cout << endl
      //      << "restore var id: " << assignmentHistory.top().first << " " << assignmentHistory.top().second.size() << endl;
      assignmentHistory.pop();
    }
  }
  depthSum += currentDepth;
  currentDepth--;

  return false;
}

/// @brief select a variable to consider next, where MRV is used
/// @return
Tile* Control::selectUnassignedVariable() {
  vector<Tile*> unassigned = getUnassignedVariables();
  if (unassigned.size() > 0) {
    return unassigned[0];
  }
  return nullptr;
}

/// @brief get all of the unassigned variables
/// @return
vector<Tile*> Control::getUnassignedVariables() {
  vector<vector<Tile*>> arr = puzzle->getPuzzleArr();

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

/// @brief order the domain values using lcv or just return the regular domain
/// @param t
/// @return
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

/// @brief forward check inference step, whittle down the domains when possible
/// @param t tile to infer the domains of the neighbors of
/// @return
bool Control::forwardCheck(Tile* t) {
  vector<Constraint*> neighbors = constraints->findConstraints(t->getId());
  vector<vector<pair<Tile*, vector<int>>>> history;
  //  cout << "check for " << t->getId() << " " << t->getNum() << " | ";
  for (Constraint* c : neighbors) {
    pair<bool, vector<pair<Tile*, vector<int>>>> res = c->removeFromDomainOfOtherTiles(t->getId(), t->getNum());

    if (!res.first) {
      restoreNeighborsForForwardCheck(history);  // there's still stuff to restore, maybe from BinaryArcs, other edits
      return false;                              // if we found an inconsistency we shouldn't push further
    }
    history.push_back(res.second);
  }
  //  cout << endl;

  // add to history of changes
  inferenceHistory.push(history);
  return true;
}

/// @brief restore the neighbors after a forward check
/// @param history
void Control::restoreNeighborsForForwardCheck(vector<vector<pair<Tile*, vector<int>>>> history) {
  // cout << endl
  //    << "restore: ";

  for (vector<pair<Tile*, vector<int>>> toRestore : history) {
    for (pair<Tile*, vector<int>> x : toRestore) {
      //    cout << x.first->getId() << " ";
      Tile* tile = x.first;

      tile->restoreDomain(x.second);
    }
    //  cout << " | ";
  }
  // cout << endl;
}

/// @brief check if an assignment was consistent
/// @param tileId
/// @param proposedAssignment
/// @return
bool Control::checkConsistent(string tileId, int proposedAssignment) {
  vector<Constraint*> neighbors = constraints->findConstraints(tileId);

  for (Constraint* c : neighbors) {
    if (!(c->proposeAssignment(tileId, proposedAssignment))) return false;
  }
  return true;
}

/// @brief creates a sum constraint given a vector of tiles
/// @param tiles
/// @return
Sum* Control::createSumHelper(vector<int> tiles) {
  int runningSum = 0;
  vector<Tile*> toPass;
  for (int x : tiles) {
    int row = x / 9;
    int col = x % 9;
    toPass.push_back(puzzle->getTile(row, col));
    runningSum += solution->getTile(row, col)->getNum();
  }
  if ((int)toPass.size() == 1) {
    toPass[0]->setNum(runningSum);
  }
  //  cout << "total sum: " << runningSum << endl;
  return new Sum(runningSum, toPass);
}