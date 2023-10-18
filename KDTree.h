#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <limits>
#include <random>
#include <vector>
using namespace std;

#include "Point.h"

class KDTree {
 public:
  KDTree(int k);
  KDTree(int n, int k);
  ~KDTree();
  virtual void insert(const Point &p);
  Point findNearestNeighbor(const Point &p, int &numNodesVisited);
  void print();
  int typeOfTree;//0->Standard 1->Relaxed 2->Squarish

 protected:
  struct Node {
    Point p;
    Node *left;
    Node *right;
    int level;
    int discriminant;
    Node(const Point &p, int level, int discriminant);
  };

  Node *root;
  int k;
  void deleteRecursive(Node *node);
  virtual void insertRecursive(Node *node, const Point &p);
  bool radiusCrossesRightBoundingBox(Node *node, const Point &p, float dist);
  bool radiusCrossesLeftBoundingBox(Node *node, const Point &p, float dist);
  void findNearestNeighborRecursive(Node *node, const Point &p, float &dist,
                                    Point &best, int &numNodesVisited);
  void printNode(Node *node);
};

#endif  // KDTREE_H