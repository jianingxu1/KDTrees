#include "RelaxedKDTree.h"

RelaxedKDTree::RelaxedKDTree(int k) : KDTree(k) {
  random_device myRandomDevice;
  unsigned seed = myRandomDevice();
  this->Uniform = uniform_int_distribution<int>(0, k - 1);
  this->RNG = default_random_engine(seed);
}

RelaxedKDTree::RelaxedKDTree(int n, int k) : KDTree(n, k) {
  random_device myRandomDevice;
  unsigned seed = myRandomDevice();
  this->Uniform = uniform_int_distribution<int>(0, k - 1);
  this->RNG = default_random_engine(seed);
}
void RelaxedKDTree::insert(const Point &p) {
  if (root == nullptr) {
    root = new Node(p, 0, getRandomDiscriminant());
    return;
  }
  insertRecursive(root, p);
}

void RelaxedKDTree::insertRecursive(Node *node, const Point &p) {
  int discriminant = node->discriminant;
  if (p.coords[discriminant] < node->p.coords[discriminant]) {
    if (node->left == nullptr) {
      int newLevel = node->level + 1;
      int newDiscriminant = getRandomDiscriminant();
      node->left = new Node(p, newLevel, newDiscriminant);
      return;
    }
    insertRecursive(node->left, p);
  } else {
    if (node->right == nullptr) {
      int newLevel = node->level + 1;
      int newDiscriminant = getRandomDiscriminant();
      node->right = new Node(p, newLevel, newDiscriminant);
      return;
    }
    insertRecursive(node->right, p);
  }
}

int RelaxedKDTree::getRandomDiscriminant() { return Uniform(RNG); }