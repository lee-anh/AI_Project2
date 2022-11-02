#include "BinaryArc.h"

BinaryArc::BinaryArc(string id1, string id2) {
  this->id1 = id1;
  this->id2 = id2;
}

string BinaryArc::getId1() {
  return id1;
}

string BinaryArc::getId2() {
  return id2;
}
