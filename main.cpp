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
  int numTrees, numNodes, numQueries, k;
  // cout << "Introduce the dimension:\n";
  cin >> k;
  numTrees = 30;
  numNodes = 1000000;
  numQueries = 10000;  


  for(int typeOfTree = 0; typeOfTree < 3; ++typeOfTree){ //For que pasa por los 3 tipos de arboles

    for (int n = numNodes; n <= 10000000; n+=1000000) { //For que itera por diferentes tamaños de arboles

      cout << n << ' ';

      // Queremos utilizar las mismas queries para todos los arboles de
      // una misma mida para disminuir la varianza
      vector<Point> queries = generateQueries(numQueries, k);

      for (int i = 0; i < numTrees; ++i) { //For que crea T arboles y hace la cerca de Q queries
      //La creacion de los arboles dependen de que tipo de arbol estamos tratando

        int nodesVisited = 0;
        int avgNodesVisited_per_size = 0;
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

        //Para cada arbol tratado, queremos saber la media de nodos visitados en los Q queries
        //Esto lo usaremos para calcular la MEDIA de medias de los T arboles y para
        //calcular la VARIANZA de estas medias en los T arboles
        avgNodesVisited_per_size = nodesVisited / numQueries;
        cout << avgNodesVisited_per_size << ' ';
      }
        //Delimita las diferentes midas que van a tener los arboles
        cout << endl;
    }
    //Delimita los diferentes tipos de arboles implementados
    cout << endl;
  }
}
