#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>

struct Point {
  std::vector<float> coords;
  Point(const std::vector<float> &coords);
};

class KDTree {
 public:
  KDTree();
  ~KDTree();
  void insert(const Point &p);
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
  void printNode(Node *node);
};

#endif  // KDTREE_H