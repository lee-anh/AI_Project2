#ifndef CONTROL_H
#define CONTROL_H

#include <chrono>
#include <iostream>
#include <queue>
#include <stack>

#include "CSP.h"
#include "Checker.h"
#include "Puzzle.h"

using namespace std;

class Control {
 public:
  /// @brief Control Constructor
  /// @param filename
  /// @param outputFilename
  /// @param type
  /// @param useAc3
  /// @param useMinRemainingValues
  /// @param useLeastConstrainingValue
  /// @param useForwardChecking
  Control(string filename, string outputFilename, puzzleType type, bool useAc3, bool useMinRemainingValues, bool useLeastConstrainingValue, bool useForwardChecking);

  /// @brief print puzzle stats to terminal
  void printPuzzleData();

  /// @brief write data to log file
  void writeDataToLog();

  /// @brief Callee for recursive backtracking()
  void backtrackingSearch();

 private:
  string outputFilename;
  Puzzle* puzzle;
  Puzzle* solution;  // only used for Killer Sudoku
  puzzleType type;
  bool useAc3;
  bool useMinRemainingValues;
  bool useLeastConstrainingValue;
  bool useForwardChecking;
  bool isSolution;
  int backtrackCalled;
  int currentDepth;
  long long depthSum;
  int timeToSolve;

  int numUnassignedAfterAc3;
  float averageDomainSizeAfterAc3;

  CSP* constraints;

  // stack of changes
  stack<vector<int>> assignmentHistory;
  stack<vector<vector<pair<Tile*, vector<int>>>>> inferenceHistory;

  // sum constraints to add after ac3
  vector<Sum*> sumConstraints;

  /// @brief read in a Standard or overlapping puzzle
  /// @param filename
  /// @param side 9 if standard, 15 if overlapping
  void readInStandard(string filename, int side);

  /// @brief read in a killer puzzle
  /// @param filename
  void readInKiller(string filename);

  /// @brief AC-3 preprocessing
  /// @return true if assignments were successfully made, false if we ran into a no solution scenario
  bool ac3();

  /// @brief recursive backtrack
  /// @return
  bool backtrack();

  /// @brief select a variable to consider next, where MRV is used
  /// @return
  Tile* selectUnassignedVariable();

  /// @brief get all of the unassigned variables
  /// @return
  vector<Tile*> getUnassignedVariables();

  /// @brief order the domain values using lcv or just return the regular domain
  /// @param t
  /// @return
  vector<int> orderDomainValues(Tile* t);

  /// @brief forward check inference step
  /// @param t tile to infer the domains of the neighbors of
  /// @return
  bool forwardCheck(Tile* t);

  /// @brief restore the neighbors after a forward check
  /// @param history
  void restoreNeighborsForForwardCheck(vector<vector<pair<Tile*, vector<int>>>> history);

  /// @brief check if an assignment was consistent
  /// @param tileId
  /// @param proposedAssignment
  /// @return
  bool checkConsistent(string tileId, int proposedAssignment);

  /// @brief creates a sum constraint given a vector of tiles
  /// @param tiles
  /// @return
  Sum* createSumHelper(vector<int> tiles);
};

#endif