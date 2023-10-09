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
  void insert(const Point &p);
  Point findNearestNeighbor(const Point &p, int &numNodesVisited);
  void print();

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
  void insertRecursive(Node *node, const Point &p);
  bool radiusCrossesRightBoundingBox(Node *node, const Point &p, float dist);
  bool radiusCrossesLeftBoundingBox(Node *node, const Point &p, float dist);
  void findNearestNeighborRecursive(Node *node, const Point &p, float &dist,
                                    Point &best, bool &hasFoundLeaf,
                                    int &numNodesVisited);
  void findNearestNeighborCandidateIterative(Node *node, const Point &p,
                                             float &dist, Point &best);
  void printNode(Node *node);
};

#endif  // KDTREE_H