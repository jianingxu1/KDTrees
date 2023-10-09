#ifndef RELAXEDKDTREE_H
#define RELAXEDKDTREE_H

#include "KDTree.h"

class RelaxedKDTree : public KDTree {
 public:
  RelaxedKDTree(int k);
  RelaxedKDTree(int n, int k);
  void insert(const Point &p) override;

 protected:
  void insertRecursive(Node *node, const Point &p) override;
  int getRandomDiscriminant();
  default_random_engine RNG;
  uniform_int_distribution<int> Uniform;
};

#endif  // RELAXEDKDTREE_H
