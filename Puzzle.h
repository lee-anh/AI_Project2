#ifndef PUZZLE
#define PUZZLE

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

using namespace std;

class Puzzle {
 public:
  Puzzle();
  // we should probably read in the puzzle now
  // what should the puzzle even be able to do?

  // is this the level where we should start considering out constraints?

 private:
  vector<vector<Tile*>> arr;  // we already know the size?
  class Tile {
   public:
    // we should start with a full domain and be able to remove from it
    // we don't know the assignment
    Tile() {
      Tile(0);
    }

    // I think basic functionality here

    // we know the assignment ahead of time, so we wouldn't care about the domain
    Tile(int num) {
      this->num = num;
      if (num == 0) {
        for (int i = 1; i < 10; i++) {
          domain.push_back(i);
        }
      }
    }
    // do we fill up the domain
    int num;  // the number it's been assigned
    vector<int> domain;

    // don't know if we will even need this
    int getDomainSize() {
      return (int)domain.size();
    }

    void removeFromDomain(int val) {
      int index = -1;
      for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == val) {
          index = i;
          break;
        }
      }
      if (index != -1) {
        arr.erase(arr.begin(), arr.begin() + index);
      }
    }
  };

  // what about the puzzle with the
};

#endif