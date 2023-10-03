#include <iostream>
#include <vector>

#include "kdtree.h"
using namespace std;

int main() {
  KDTree tree;
  tree.insert(Point({10, 20}));
  tree.insert(Point({5, 30}));
  tree.insert(Point({8, 40}));
  tree.insert(Point({15, 25}));
  tree.insert(Point({100, 30}));
  tree.insert(Point({7, 15}));
  tree.print();
  return 0;
}