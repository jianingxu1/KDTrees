#include <time.h>

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "KDTree.h"
#include "RelaxedKDTree.h"
#include "SquarishKDTree.h"
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

int varianza(vector<int>& V, int avg) {
  int sum_squared_diff = 0;
  int n = V.size();
  // Calcula la suma de los cuadrados de las diferencias
  for (int i = 0; i < n; i++) {
    int diff = V[i] - avg;
    sum_squared_diff += diff * diff;
    // cout <<V[i] << " ";
  }
  // Calcula la varianza
  int variance = sum_squared_diff / (n - 1);

  return variance;
}

int main() {
  int numTrees, numNodes, numQueries, k, typeOfTree;
  cout << "Enter the type of KD-Tree:\n 0(Standard)\n 1(Relaxed)\n "
          "2(Squarish)\n";
  cin >> typeOfTree;
  cout << "Introduce the dimension:\n";
  cin >> k;
  numTrees = 100;
  numNodes = 1000;
  numQueries = 1000000;  // Como las queries tardan poco, podemos hacer muchas
                         // queries para que la media sea mas precisa

  for (int n = numNodes; n <= 1000; n *= 10) {
    long int avgNodesVisited_per_size = 0;
    int var = 0;  // Acumulador de varianzas
    // Queremos utilizar las mismas queries para todos los arboles de
    // una misma mida para disminuir la varianza
    vector<Point> queries = generateQueries(numQueries, k);
    for (int i = 0; i < numTrees; ++i) {
      int nodesVisited = 0;
      vector<int> variQ(numQueries, 0);  // aqui iremos guardando cuantos nodo
      if (typeOfTree == 0) {
        KDTree tree(n, k);
        for (int j = 0; j < numQueries; ++j) {
          int curNodesVisited = 0;
          tree.findNearestNeighbor(queries[j], curNodesVisited);
          nodesVisited += curNodesVisited;
          variQ[j] = curNodesVisited;
        }
      } else if (typeOfTree == 1) {
        RelaxedKDTree tree(n, k);
        for (int j = 0; j < numQueries; ++j) {
          int curNodesVisited = 0;
          tree.findNearestNeighbor(queries[j], curNodesVisited);
          nodesVisited += curNodesVisited;
          variQ[j] = curNodesVisited;
        }
      } else if (typeOfTree == 2) {
        SquarishKDTree tree(n, k);
        for (int j = 0; j < numQueries; ++j) {
          int curNodesVisited = 0;
          tree.findNearestNeighbor(queries[j], curNodesVisited);
          nodesVisited += curNodesVisited;
          variQ[j] = curNodesVisited;
        }
      } else {
        cout << "Error: type of tree not valid" << endl;
        return 0;
      }

      // vas acumulando la suma de medias de todos los arboles de la mida n
      // actual
      avgNodesVisited_per_size += nodesVisited / numQueries;
      var += varianza(variQ, avgNodesVisited_per_size);
    }
    // media de la suma de las medias de los 100 arboles
    cout << avgNodesVisited_per_size / numTrees << " ";
    // media de la suma de las medias de los 100 arboles
    cout << var / numTrees << endl;
  }
}
