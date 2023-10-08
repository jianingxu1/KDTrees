#include <time.h>

#include <iostream>
#include <random>
#include <vector>

#include "KDTree.h"
using namespace std;

// Random uniform number generator between 0 and 1
mt19937 gen(time(NULL));
uniform_real_distribution<float> dis(0.0f, 1.0f);

vector<Point> generateQueries(int numQueries, int k) {
  vector<Point> queries(numQueries);
  for (int i = 0; i < numQueries; ++i) {
    vector<float> coords(k);
    for (int j = 0; j < k; ++j) {
      coords[j] = dis(gen);
    }
    Point p(coords);
    queries[i] = p;
  }
  return queries;
}

int main() {
  int numTrees, numNodes, numQueries, k,typeOfTree;
  cout << "Introduce the number of trees, nodes, queries, dimensions:\n";
  cin >> numTrees >> numNodes >> numQueries >> k;
  cout << "Enter the type of KD-Tree:\n 0(Standard)\n 1(Relaxed)\n 2(Squarish)\n";
  cin >> typeOfTree;
  cout << endl;
  
  vector<Point> queries = generateQueries(numQueries, k);

  // Create trees one by one, and execute queries
  for (int i = 0; i < numTrees; ++i) {
    // Create tree
    KDTree tree(numNodes, k,typeOfTree);

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