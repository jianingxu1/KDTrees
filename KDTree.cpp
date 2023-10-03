#include "KDTree.h"

KDTree::KDTree() : root(nullptr) {}

KDTree::~KDTree() { deleteRecursive(root); }

void KDTree::insert(const Point &p) {
  if (root == nullptr) {
    root = new Node(p, 0);
    return;
  }
  insertRecursive(root, p);
}

void KDTree::print() {
  std::cout << "Inorder traversal: ";
  printNode(root);
  std::cout << std::endl;
}

Point KDTree::findNearestNeighbor(const Point &p) {
  float dist = MAXFLOAT;
  Point best;
  findNearestNeighborCandidateIterative(root, p, dist, best);
  return best;
}

KDTree::Node::Node(const Point &p, int level)
    : p(p), left(nullptr), right(nullptr), level(level) {}

int KDTree::Node::getDiscriminant() { return level % p.coords.size(); }

void KDTree::deleteRecursive(Node *node) {
  if (node == nullptr) {
    return;
  }
  deleteRecursive(node->left);
  deleteRecursive(node->right);
  delete node;
}

void KDTree::insertRecursive(Node *node, const Point &p) {
  int discriminant = node->getDiscriminant();
  if (p.coords[discriminant] < node->p.coords[discriminant]) {
    if (node->left == nullptr) {
      node->left = new Node(p, node->level + 1);
      return;
    }
    insertRecursive(node->left, p);
  } else {
    if (node->right == nullptr) {
      node->right = new Node(p, node->level + 1);
      return;
    }
    insertRecursive(node->right, p);
  }
}

void KDTree::findNearestNeighborCandidateIterative(Node *node, const Point &p,
                                                   float &dist, Point &best) {
  while (node != nullptr) {
    float currentDist = p.distanceTo(node->p);
    if (currentDist < dist) {
      dist = currentDist;
      best = node->p;
    }
    int discriminant = node->getDiscriminant();
    if (p.coords[discriminant] < node->p.coords[discriminant])
      node = node->left;
    else
      node = node->right;
  }
}

void KDTree::printNode(Node *node) {
  if (node == nullptr) {
    return;
  }
  printNode(node->left);
  node->p.print();
  std::cout << ' ';
  printNode(node->right);
}
