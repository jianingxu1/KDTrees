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
  KDTree();
  KDTree(int n, int k);
  ~KDTree();
  void insert(const Point &p);
  Point findNearestNeighbor(const Point &p, int &numNodesVisited);
  void print();

 private:
  struct Node {
    Point p;
    Node *left;
    Node *right;
    int level;
    Node(const Point &p, int level);
    int getDiscriminant();
  };

  Node *root;
  void deleteRecursive(Node *node);
  void insertRecursive(Node *node, const Point &p);
  bool radiusCrossesRightBoundingBox(Node *node, const Point &p, float dist);
  bool radiusCrossesLeftBoundingBox(Node *node, const Point &p, float dist);
  void findNearestNeighborRecursive(Node *node, const Point &p, float &dist,
                                    Point &best, bool &hasFoundLea,
                                    int &numNodesVisited);
  void findNearestNeighborCandidateIterative(Node *node, const Point &p,
                                             float &dist, Point &best);
  void printNode(Node *node);
};

#endif  // KDTREE_H