#include "KDTree.h"

KDTree::KDTree(int k) : root(nullptr), k(k) {}

KDTree::KDTree(int n, int k) {
  random_device myRandomDevice;
  unsigned seed = myRandomDevice();
  uniform_real_distribution<double> Uniform(0.0, 1.0);
  default_random_engine RNG(seed);

  root = nullptr;
  this->k = k;
  for (int i = 0; i < n; ++i) {
    vector<float> coords(k);
    for (int j = 0; j < k; ++j) {
      coords[j] = Uniform(RNG);
    }
    Point p(coords);
    insert(p);
  }
}

KDTree::~KDTree() { deleteRecursive(root); }

void KDTree::insert(const Point &p) {
  if (root == nullptr) {
    root = new Node(p, 0, 0);
    return;
  }
  insertRecursive(root, p);
}

void KDTree::print() {
  std::cout << "Inorder traversal: ";
  printNode(root);
  std::cout << std::endl;
}

Point KDTree::findNearestNeighbor(const Point &p, int &numNodesVisited) {
  float dist = std::numeric_limits<float>::infinity();
  Point best;
  findNearestNeighborRecursive(root, p, dist, best, numNodesVisited);
  return best;
}

KDTree::Node::Node(const Point &p, int level, int discriminant)
    : p(p), left(nullptr), right(nullptr), level(level), discriminant(discriminant){}


void KDTree::deleteRecursive(Node *node) {
  if (node == nullptr) {
    return;
  }
  deleteRecursive(node->left);
  deleteRecursive(node->right);
  delete node;
}

void KDTree::insertRecursive(Node *node, const Point &p) {
  int discriminant = node->discriminant;
  if (p.coords[discriminant] < node->p.coords[discriminant]) {
    if (node->left == nullptr) {
      int newLevel = node->level + 1;
      int newDiscriminant = newLevel % this->k;
      node->left = new Node(p, newLevel, newDiscriminant);
      return;
    }
    insertRecursive(node->left, p);
  } else {
    if (node->right == nullptr) {
      int newLevel = node->level + 1;
      int newDiscriminant = newLevel % this->k;
      node->right = new Node(p, newLevel, newDiscriminant);
      return;
    }
    insertRecursive(node->right, p);
  }
}

bool KDTree::radiusCrossesRightBoundingBox(Node *node, const Point &p,
                                           float dist) {
  int discr = node->discriminant;
  return p.coords[discr] + dist > node->p.coords[discr];
}

bool KDTree::radiusCrossesLeftBoundingBox(Node *node, const Point &p,
                                          float dist) {
  int discr = node->discriminant;
  return p.coords[discr] - dist < node->p.coords[discr];
}

void KDTree::findNearestNeighborRecursive(Node *node, const Point &p,
                                          float &dist, Point &best,
                                          int &numNodesVisited) {
  if (node == nullptr) return;
  ++numNodesVisited;
  float currentDist = p.distanceTo(node->p);
  if (currentDist < dist) {
    dist = currentDist;
    best = node->p;
  }
  int discriminant = node->discriminant;
  bool shouldVisitLeft = p.coords[discriminant] < node->p.coords[discriminant];

  if (shouldVisitLeft) {
    findNearestNeighborRecursive(node->left, p, dist, best, numNodesVisited);
    if (radiusCrossesRightBoundingBox(node, p, dist))
      findNearestNeighborRecursive(node->right, p, dist, best, numNodesVisited);
  }
  else {
    findNearestNeighborRecursive(node->right, p, dist, best, numNodesVisited);
    if (radiusCrossesLeftBoundingBox(node, p, dist))
      findNearestNeighborRecursive(node->left, p, dist, best, numNodesVisited);
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