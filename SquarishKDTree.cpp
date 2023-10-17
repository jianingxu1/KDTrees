#include "SquarishKDTree.h"

SquarishKDTree::SquarishKDTree(int k) : KDTree(k) {}

SquarishKDTree::SquarishKDTree(int n, int k) : KDTree(k) {
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

void SquarishKDTree::insert(const Point &p) {
  vector<pair<double, double>> boundingBox(k, pair<double, double>(0.0, 1.0));
  if (root == nullptr) {
    root = new Node(p, 0, getBestDiscriminant(p, boundingBox));
    return;
  }
  insertRecursiveBb(root, p, boundingBox);
}

void SquarishKDTree::insertRecursiveBb(
    Node *node, const Point &p, vector<pair<double, double>> &boundingBox) {
  int discriminant = node->discriminant;
  if (p.coords[discriminant] < node->p.coords[discriminant]) {
    boundingBox[discriminant].second = node->p.coords[discriminant];
    if (node->left == nullptr) {
      int newLevel = node->level + 1;
      int newDiscriminant = getBestDiscriminant(p, boundingBox);
      node->left = new Node(p, newLevel, newDiscriminant);
      return;
    }
    insertRecursiveBb(node->left, p, boundingBox);
  } else {
    boundingBox[discriminant].first = node->p.coords[discriminant];
    if (node->right == nullptr) {
      int newLevel = node->level + 1;
      int newDiscriminant = getBestDiscriminant(p, boundingBox);
      node->right = new Node(p, newLevel, newDiscriminant);
      return;
    }
    insertRecursiveBb(node->right, p, boundingBox);
  }
}

int SquarishKDTree::getBestDiscriminant(const Point &p, const vector<pair<double, double>> &boundingBox) {
  int dimension = -1;
  double maxSideLength = -1.0;

  // Iterate through each dimension
  for (int i = 0; i < boundingBox.size(); i++) {
      double sideLength = boundingBox[i].second - boundingBox[i].first;

      // Calculate the distance of the point to the midpoint of the current dimension
      double midpoint = (boundingBox[i].first + boundingBox[i].second) / 2.0;
      double distanceToMidpoint = abs(p.coords[i] - midpoint);

      // Update the dimension if the side length is the longest so far
      if (sideLength > maxSideLength && distanceToMidpoint <= sideLength / 2.0) {
          maxSideLength = sideLength;
          dimension = i;
      }
  }
  return dimension; 
}