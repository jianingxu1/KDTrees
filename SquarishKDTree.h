#ifndef SQUARISHKDTREE_H
#define SQUARISHKDTREE_H

#include "KDTree.h"

class SquarishKDTree : public KDTree {
 public:
  SquarishKDTree(int k);
  SquarishKDTree(int n, int k);

  void insert(const Point &p) override;

 protected:
  void insertRecursiveBb(Node *node, const Point &p, vector<pair<double, double>> &boundingBox);
  int getMaxDimensionDiscriminant(const vector<pair<double, double>> &boundingBox);
  int getBestDiscriminant(const Point &p, const vector<pair<double, double>> &boundingBox);
};

#endif  // SQUARISHKDTREE_H
