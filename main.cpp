#include <iostream>
#include <vector>

#include "KDTree.h"
#include "Point.h"
using namespace std;

int main() {
  KDTree tree;
  tree.insert(Point({0.3, 0.8}));
  tree.insert(Point({0.2, 0.4}));
  tree.insert(Point({0.5, 0.6}));
  tree.insert(Point({0.6, 0.1}));
  tree.insert(Point({0.8, 0.4}));
  tree.insert(Point({1.0, 0.2}));
  tree.insert(Point({0.9, 0.8}));
  tree.insert(Point({0.7, 0.6}));
  tree.insert(Point({0.75, 0.65}));
  tree.print();

  Point p = tree.findNearestNeighbor(Point({0.7, 0.7}));
  p.print();
  cout << endl;
}