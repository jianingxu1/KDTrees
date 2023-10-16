#include <time.h>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>

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

float varianza(vector<float>& V, float avg) {
  float sum_squared_diff = 0;
  int n = V.size();
  // Calcula la suma de los cuadrados de las diferencias
  for (int i = 0; i < n; i++) {
    float diff = V[i] - avg;
    sum_squared_diff += diff * diff;
  }
  // Calcula la varianza
  float variance = sum_squared_diff / (float) (n - 1);

  return variance;
}

int main() {
  int k, typeOfTree;
  cout << "Enter type of tree [0 Stand, 1 Rel, 2 Squa] and k \n";
  cin >> typeOfTree >> k;

  vector<string> typeTree = { "Standard", "Relaxed", "Squarish" };

  string filename = "data/" + typeTree[typeOfTree] + "K" + to_string(k) + ".csv"; 
  ofstream outputFile(filename);

  if (!outputFile) {
    std::cerr << "Error: Could not open the file." << std::endl;
    return 1;
  }

  int numTrees = 100;
  int numNodes = 2000;
  int numQueries = 10000;  
    
  outputFile << "Type, K, N, Mean, Variance\n";
  
  for (int n = numNodes; n <= 100000; n+=2000) {
    // Queremos utilizar las mismas queries para todos los arboles de
    // una misma mida para disminuir la varianza
    vector<Point> queries = generateQueries(numQueries, k);
    float avgNodesVisitedForAllTrees = 0;

    vector<float> meanForTree(numTrees, 0);
    
    for (int i = 0; i < numTrees; ++i) { //For que crea T arboles y hace la cerca de Q queries
      //La creacion de los arboles dependen de que tipo de arbol estamos tratando
      float avgNodesVisitedForOneTree = 0;
      if (typeOfTree == 0) {
        KDTree tree(n, k);
        for (int j = 0; j < numQueries; ++j) {
          int curNodesVisited = 0;
          tree.findNearestNeighbor(queries[j], curNodesVisited);
          avgNodesVisitedForOneTree += curNodesVisited;
        }
      }
      else if (typeOfTree == 1) {
        RelaxedKDTree tree(n, k);
        for (int j = 0; j < numQueries; ++j) {
          int curNodesVisited = 0;
          tree.findNearestNeighbor(queries[j], curNodesVisited);
          avgNodesVisitedForOneTree += curNodesVisited;
        }
      }
      else if (typeOfTree == 2) {
        SquarishKDTree tree(n, k);
        for (int j = 0; j < numQueries; ++j) {
          int curNodesVisited = 0;
          tree.findNearestNeighbor(queries[j], curNodesVisited);
          avgNodesVisitedForOneTree += curNodesVisited;
        }
      }
      else {
        cerr << "Wrong type of tree\n";
        return 1;
      }
      
      //Para cada arbol tratado, queremos saber la media de nodos visitados en los Q queries
      //Esto lo usaremos para calcular la MEDIA de medias de los T arboles y para
      avgNodesVisitedForOneTree /= (float) numQueries; 
      
      avgNodesVisitedForAllTrees += avgNodesVisitedForOneTree;
      
      meanForTree[i] = avgNodesVisitedForOneTree;
      
    }
    //Delimita las diferentes midas que van a tener los arboles
    avgNodesVisitedForAllTrees /= (float) numTrees;
        
    outputFile << typeTree[typeOfTree] <<','<< k <<',' << n <<',' << avgNodesVisitedForAllTrees  << ',' << sqrt(varianza(meanForTree, avgNodesVisitedForAllTrees)) << endl;
  }
 //Delimita los diferentes tipos de arboles implementados
  outputFile.close();
}


/* 

  for numNodes=2000 to 100000

    avgNodesAllTrees = 0
    meanForTree[numTrees] = []
    for numTrees=1 to 100


      avgNodes = 0
      for numQueries=1 to 1000
        avgNodes += currentNodes
      avgNodes /= numQueries
      meanForTree[numTrees] = avgNodes
      avgNodesAllTrees += avgNodes


    avgNodesAllTrees /= numTrees
    cout << avgNodes ... << varianza

*/