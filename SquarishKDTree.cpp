#include "SquarishKDTree.h"

SquarishKDTree::SquarishKDTree(int k) : KDTree(k) {}

SquarishKDTree::SquarishKDTree(int n, int k) : KDTree(n, k) {}

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

int SquarishKDTree::getMaxDimensionDiscriminant(const vector<pair<double, double>> &boundingBox) {
  vector<int> dimensionLength(k);

  int maxDimension = 0;
  for (int i = 0; i < k; ++i) {
    dimensionLength[i] = boundingBox[i].second - boundingBox[i].first;
    if (dimensionLength[i] > dimensionLength[maxDimension]) maxDimension = i;
  }
  return maxDimension;
}

int SquarishKDTree::getBestDiscriminant(const Point &p, const vector<pair<double, double>> &boundingBox) {
  vector<double> dimensionLength(k);
  for (int i = 0; i < k; ++i) {
    dimensionLength[i] = boundingBox[i].second - boundingBox[i].first;
  }
  vector<double> prefixMult(k);
  prefixMult[0] = 1;
  for (int i = 1; i < k; ++i) {
    prefixMult[i] = prefixMult[i - 1] * dimensionLength[i - 1];
  }
  vector<double> suffixMult(k);
  suffixMult[k - 1] = 1;
  for (int i = k - 2; i >= 0; --i) {
    suffixMult[i] = suffixMult[i + 1] * dimensionLength[i + 1];
  }
  vector<double> maxNewBb(k);
  for (int i = 0; i < k; ++i) {
    maxNewBb[i] = max(p.coords[i] - boundingBox[i].first,
                      boundingBox[i].second - p.coords[i]);
  }
  int bestDiscriminant = 0;
  for (int i = 1; i < k; ++i) {
    if (maxNewBb[i] * prefixMult[i] * suffixMult[i] <
        maxNewBb[bestDiscriminant] * prefixMult[bestDiscriminant] *
            suffixMult[bestDiscriminant]) {
      bestDiscriminant = i;
    }
  }
  return bestDiscriminant;
}