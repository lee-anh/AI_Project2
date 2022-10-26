#include "Tile.h"

// we know the assignment ahead of time, so we wouldn't care about the domain
Tile::Tile(int num, int x, int y) {
  this->num = num;
  if (num == 0) {  // we don't know the assignment ahead of time
    for (int i = 1; i < 10; i++) {
      domain.push_back(i);
    }
  } else {
    domain.push_back(num);  // the domain should just be that number
  }
  id = to_string(x) + to_string(y);
}

vector<int> Tile::getDomain() {
  return domain;
}

string Tile::getId() {
  return id;
}

// don't know if we will even need this
int Tile::getDomainSize() {
  return (int)domain.size();
}

int Tile::getNum() {
  return num;
}

void Tile::trySetNum() {
  if ((int)domain.size() == 1) {
    num = domain[0];
  }
  // else we don't assign num yet
}

void Tile::removeFromDomain(int val) {
  int index = -1;
  for (int i = 0; i < (int)domain.size(); i++) {
    if (domain[i] == val) {
      index = i;
      break;
    }
  }
  if (index != -1) {
    domain.erase(domain.begin() + index);
    trySetNum();
  }
}

void Tile::printTile() {
  cout << "Id: " << id << " Assignment: " << num << " Domain: ";
  for (int i = 0; i < (int)domain.size(); i++) {
    cout << domain[i] << " ";
  }
  cout << endl;
}