#include <time.h>
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
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

int varianza(vector<int>& V, int avg) {
    int sum_squared_diff = 0;
    int n = V.size();

    // Calcula la suma de los cuadrados de las diferencias
    for (int i = 0; i < n; i++) {
        int diff = V[i] - avg;
        sum_squared_diff += diff * diff;
        //cout <<V[i] << " ";
    }

    // Calcula la varianza
    int variance = sum_squared_diff / (n-1);
    
    return variance;
}


int main() {
  int numTrees, numNodes, numQueries, k,typeOfTree;
  cout << "Enter the type of KD-Tree:\n 0(Standard)\n 1(Relaxed)\n 2(Squarish)\n";
  cin >> typeOfTree;
  cout << "Introduce the dimension:\n";
  numTrees = 100;
  numNodes = 10000;
  numQueries = 100;
  cin >> k;

  
for (int nodes_act = numNodes; nodes_act <= 1000000; nodes_act+=10000) {
    long int avgNodesVisited_per_size = 0;
    int v = 0; //aqui ire acomulando las varianzas para cada arbol
    // Create trees one by one, and execute queries
        vector<Point> queries = generateQueries(numQueries, k); //seria interesante que cambien los arboles y tambien los queries
    for (int i = 0; i < numTrees; ++i) {
        // Create tree
        KDTree tree(numNodes, k,typeOfTree);
        // Execute queries100
        int nodesVisited = 0;
        vector<int> variQ(numQueries,0); //aqui iremos guardando cuantos nodo
        for (int j = 0; j < numQueries; ++j) {
          int curNodesVisited = 0;
          tree.findNearestNeighbor(queries[j], curNodesVisited);
          nodesVisited += curNodesVisited;
          variQ[j] = curNodesVisited;

          // cout << curNodesVisited << endl;
        }
        avgNodesVisited_per_size += nodesVisited / numQueries; //vas acumulando la suma de medias de todos los arbooles de la mida n actual
        v += varianza(variQ,avgNodesVisited_per_size);

    }
    cout<<avgNodesVisited_per_size/numTrees<<" "; //media de la suma de las medias de los 100 arboles
    cout<<v/numTrees<<endl; //media de la suma de las medias de los 100 arboles 

  }

}