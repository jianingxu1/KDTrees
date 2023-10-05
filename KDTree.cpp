#include "KDTree.h"

KDTree::KDTree() : root(nullptr) {}

KDTree::KDTree(int n, int k) {
  mt19937 gen(time(NULL) + 10);
  uniform_real_distribution<float> dis(0.0f, 1.0f);
  root = nullptr;
  for (int i = 0; i < n; ++i) {
    vector<float> coords(k);
    for (int j = 0; j < k; ++j) {
      coords[j] = dis(gen);
    }
    Point p(coords);
    insert(p);
  }
}

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

Point KDTree::findNearestNeighbor(const Point &p, int &numNodesVisited) {
  float dist = std::numeric_limits<float>::infinity();
  Point best;
  bool hasFoundLeaf = false;
  findNearestNeighborRecursive(root, p, dist, best, hasFoundLeaf,
                               numNodesVisited);
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

bool KDTree::radiusCrossesRightBoundingBox(Node *node, const Point &p,
                                           float dist) {
  int discr = node->getDiscriminant();
  return p.coords[discr] + dist > node->p.coords[discr];
}

bool KDTree::radiusCrossesLeftBoundingBox(Node *node, const Point &p,
                                          float dist) {
  int discr = node->getDiscriminant();
  return p.coords[discr] - dist < node->p.coords[discr];
}

void KDTree::findNearestNeighborRecursive(Node *node, const Point &p,
                                          float &dist, Point &best,
                                          bool &hasFoundLeaf,
                                          int &numNodesVisited) {
  if (node == nullptr) return;
  ++numNodesVisited;
  float currentDist = p.distanceTo(node->p);
  if (currentDist < dist) {
    dist = currentDist;
    best = node->p;
  }
  int discriminant = node->getDiscriminant();
  if (not hasFoundLeaf) {
    if (p.coords[discriminant] < node->p.coords[discriminant]) {
      if (node->left != nullptr)
        findNearestNeighborRecursive(node->left, p, dist, best, hasFoundLeaf,
                                     numNodesVisited);

      hasFoundLeaf = true;
      if (radiusCrossesRightBoundingBox(node, p, dist))
        findNearestNeighborRecursive(node->right, p, dist, best, hasFoundLeaf,
                                     numNodesVisited);

    } else {
      if (node->right != nullptr)
        findNearestNeighborRecursive(node->right, p, dist, best, hasFoundLeaf,
                                     numNodesVisited);

      hasFoundLeaf = true;
      if (radiusCrossesLeftBoundingBox(node, p, dist))
        findNearestNeighborRecursive(node->left, p, dist, best, hasFoundLeaf,
                                     numNodesVisited);
    }

  } else {
    if (radiusCrossesLeftBoundingBox(node, p, dist))
      findNearestNeighborRecursive(node->left, p, dist, best, hasFoundLeaf,
                                   numNodesVisited);
    if (radiusCrossesRightBoundingBox(node, p, dist))
      findNearestNeighborRecursive(node->right, p, dist, best, hasFoundLeaf,
                                   numNodesVisited);
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
