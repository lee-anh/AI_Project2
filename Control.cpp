#include "Control.h"

Control::Control(string filename, puzzleType type, bool useAc3, bool useMinRemainingValues, bool useLeastConstrainingValue, bool useForwardChecking) {
  this->type = type;
  this->useMinRemainingValues = useMinRemainingValues;
  this->useLeastConstrainingValue = useLeastConstrainingValue;
  this->useForwardChecking = useForwardChecking;

  if (type == STANDARD) {
    readInStandard(filename);
    addConstraintsStandard();
    printPuzzle();
    if (useAc3) {
      ac3();
    }
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
  backtrack();
}

bool Control::backtrack() {
  // cout << "backtrack called " << endl;
  if (puzzle->isAssignmentComplete()) {
    puzzle->printPuzzle();
    return true;
  }

  Tile* var = selectUnassignedVariable();
  // cout << "var: " << var->getId() << endl;
  vector<int> domainValues = orderDomainValues(var);
  for (int x : domainValues) {
    // if value is consistent with assignment then add {var = value to the assignment}
    if (checkConsistent(var->getId(), x)) {
      assignmentHistory.push(make_pair(var->getId(), var->getDomain()));  // add to memory
      var->setNum(x);
      // no inferences for now
      if (backtrack()) return true;
      // where should we keep the stack of inferences? here or outside?

      // really don't think this was the right thing to do
      var->restoreDomain(assignmentHistory.top().second);
      assignmentHistory.pop();
    }

    // TODO: change for general constraint
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

  return nullptr;  // will this work?
}

vector<Tile*> Control::getUnassignedVariables() {
  vector<vector<Tile*>> arr = puzzle->getPuzzleArr();

  // otherwise just consider the tiles in order
  vector<Tile*> toReturn;
  for (int i = 0; i < (int)arr.size(); i++) {
    for (int j = 0; j < (int)arr[i].size(); j++) {
      // we only want the unassigned tiles
      if (arr[i][j]->getNum() == 0) toReturn.push_back(arr[i][j]);
    }
  }

  if (useMinRemainingValues) {
    // sort the array to return by domain size, ascending
    sort(toReturn.begin(), toReturn.end(), tileLessThan());
  }

  //  for (Tile* x : toReturn) cout << x->getDomainSize() << " ";
  // cout << endl; // TODO: why does this not cause a seg fault?
  return toReturn;
}

vector<int> Control::orderDomainValues(Tile* t) {
  // we have to look up the constraint
  if (!useLeastConstrainingValue) return t->getDomain();
  vector<int> toReturn;

  vector<Constraint*> neighbors = constraints.find(t->getId())->second;
  for (Constraint* c : neighbors) {
    // count up how many constraints, do the ordering here
    // TODO: do this
  }
  return toReturn;
}

bool Control::forwardCheck(Tile* t) {
  vector<Constraint*> neighbors = constraints.find(t->getId())->second;
  for (Constraint* c : neighbors) {
    // delete from the domain
    // 🤔 if we get an empty domain, then we return false. we've found an inconsistency? or arc consistency?
    // TODO: need to do this
    // we need to make this work for the sums too
    BinaryArc* b = (BinaryArc*)c;  // hopefully everything should be ok with the casting
  }
  return true;
}

bool Control::isArcConsistent(BinaryArc* ba, int proposedAssignment) {
  Tile* t2 = puzzle->getTile(ba->getId2());

  int allowed = 0;
  for (int x : t2->getDomain()) {
    if (proposedAssignment != x) allowed++;
  }

  if (allowed == 0) {
    return false;
  }
  return true;
}

bool Control::checkConsistent(string tileId, int proposedAssignment) {
  vector<Constraint*> neighbors = constraints.find(tileId)->second;
  for (Constraint* c : neighbors) {
    if (!isArcConsistent((BinaryArc*)c, proposedAssignment)) return false;
  }
  return true;
}
