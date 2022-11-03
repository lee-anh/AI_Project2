#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <queue>
#include <stack>

#include "Puzzle.h"

using namespace std;

class Control {
 public:
  Control(string filename, puzzleType type, bool useAc3, bool useMinRemainingValues, bool useLeastConstrainingValue, bool useForwardChecking);
  void printConstraintsMap();
  void printPuzzle();
  void backtrackingSearch();

 private:
  Puzzle* puzzle;
  puzzleType type;
  bool useMinRemainingValues;
  bool useLeastConstrainingValue;
  bool useForwardChecking;

  // might make sense to make this a separate class?
  map<string, vector<Constraint*>> constraints;
  stack<pair<string, vector<int>>> assignmentHistory;
  // keep a stack of changes
  // a dictionary would be smart. what exactly are we changing?

  void addConstraintsStandard();
  void addToMap(pair<string, BinaryArc*> toAdd);
  void readInStandard(string filename);
  // only used for ac-3, which is only called once
  bool ac3();
  bool revise(BinaryArc* ba);
  // we want to keep the changes

  // backtracking stuff
  bool backtrack();

  Tile* selectUnassignedVariable();
  vector<Tile*> getUnassignedVariables();

  // TODO: these will need special return types
  vector<int> orderDomainValues(Tile* t);
  bool inference(Tile* t);
  bool forwardCheck(Tile* t);

  bool isArcConsistent(BinaryArc* ba, int proposedAssignment);

  bool checkConsistent(string tileId, int proposedAssignment);
};

#endif