#include <time.h>

#include <iostream>
#include <random>
#include <vector>

#include "KDTree.h"
using namespace std;

// Random uniform number generator between 0 and 1
  random_device myRandomDevice;
  unsigned seed = myRandomDevice();
  uniform_real_distribution<double> Uniform(0.0, 1.0);
  default_random_engine RNG(seed);

vector<Point> generateQueries(int numQueries, int k) {
  vector<Point> queries(numQueries);
  for (int i = 0; i < numQueries; ++i) {
    vector<float> coords(k);
    for (int j = 0; j < k; ++j) {
      coords[j] = Uniform(RNG);
    }
    Point p(coords);
    queries[i] = p;
  }
  return queries;
}

int main() {
  int numTrees, numNodes, numQueries, k;
  cout << "Introduce the number of trees, nodes, queries and dimensions:\n";
  cin >> numTrees >> numNodes >> numQueries >> k;

  vector<Point> queries = generateQueries(numQueries, k);

  // Create trees one by one, and execute queries
  for (int i = 0; i < numTrees; ++i) {
    // Create tree
    KDTree tree(numNodes, k);
    tree.print();
    // Execute queries
    int nodesVisited = 0;
    for (int j = 0; j < numQueries; ++j) {
      int curNodesVisited = 0;
      tree.findNearestNeighbor(queries[j], curNodesVisited);
      nodesVisited += curNodesVisited;
      // cout << curNodesVisited << endl;
    }
    int avgNodesVisited = nodesVisited /= numQueries;
    cout << avgNodesVisited << endl;
  }
}