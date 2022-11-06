#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <queue>
#include <stack>

#include "Puzzle.h"

using namespace std;

class Control {
 public:
  /// @brief Control Constructor
  /// @param filename
  /// @param type
  /// @param useAc3
  /// @param useMinRemainingValues
  /// @param useLeastConstrainingValue
  /// @param useForwardChecking
  Control(string filename, puzzleType type, bool useAc3, bool useMinRemainingValues, bool useLeastConstrainingValue, bool useForwardChecking);
  void printConstraintsMap();
  void backtrackingSearch();
  void printPuzzleData();

 private:
  Puzzle* puzzle;
  Puzzle* solution;  // only used for Killer Sudoku
  puzzleType type;
  bool useMinRemainingValues;
  bool useLeastConstrainingValue;
  bool useForwardChecking;
  int backtrackCalled;

  // might make sense to make this a separate class?
  map<string, vector<Constraint*>> constraints;

  // stack of changes==
  stack<vector<int>> assignmentHistory;
  stack<vector<pair<Tile*, vector<int>>>> inferenceHistory;

  void addConstraintsStandard();
  void addConstraintsOverlap();
  void addToMap(pair<string, BinaryArc*> toAdd);
  void readInStandard(string filename, int side);
  void readInKiller(string filename);
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
  vector<pair<Tile*, vector<int>>> forwardCheck(Tile* t);
  void restoreNeighborsForForwardCheck(vector<pair<Tile*, vector<int>>> history);

  bool checkConsistent(string tileId, int proposedAssignment);
};

#endif