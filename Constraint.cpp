#include "Constraint.h"

Constraint::Constraint(int targetSum, vector<Tile*> tiles) {
  isBinary = false;
  s = new Sum(targetSum, tiles);
}
Constraint::Constraint(Tile* t1, Tile* t2) {
  isBinary = true;
  b = new BinaryArc(t1, t2);
}

pair<int, int> Constraint::getTile1() {
  return b->getTile1();
}
pair<int, int> Constraint::getTile2() {
  return b->getTile2();
}
vector<Tile*> Constraint::getTiles() {
  return s->getTiles();
}
bool Constraint::revise() {
  return b->revise();
}
bool Constraint::proposeAssignment(string tileId, int x) {
  if (isBinary) return b->proposeAssignment(tileId, x);
  return s->proposeAssignment(tileId, x);
}
bool Constraint::willChangeDomainOfOtherTiles(string tileId, int x) {
  if (isBinary) return willChangeDomainOfOtherTiles(tileId, x);
  return s->willChangeDomainOfOtherTiles(tileId, x);
}
vector<pair<Tile*, vector<int>>> Constraint::removeFromDomainOfOtherTiles(string tileId, int x) {
  if (isBinary) return b->removeFromDomainOfOtherTiles(tileId, x);
  return s->removeFromDomainOfOtherTiles(tileId, x);
}