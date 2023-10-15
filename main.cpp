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

int main() {
  int numTrees, numNodes, numQueries, k;
  cout << "Enter the number of dimensions for the tree: \n";
  cin >> k;
  vector<string> typeTree = {"Standard","Relaxed","Squarish"};

  string filename="dimensionK"+to_string(k)+".csv"; 
  ofstream outputFile(filename);

  if (!outputFile) {
    std::cerr << "Error: Could not open the file." << std::endl;
    return 1;
  }

  outputFile << "Dimension: "<< k << endl;

  numTrees = 200;
  numNodes = 1000;
  numQueries = 10000;  

  for(int typeOfTree = 0; typeOfTree < 3; ++typeOfTree){ //For que pasa por los 3 tipos de arboles
    
    outputFile << typeTree[typeOfTree] << endl;

    for (int n = numNodes; n <= 200000; n+=2000) { //For que itera por diferentes tamaños de arboles

      outputFile << "Number of Nodes: "<<n << " Means: ";

      // Queremos utilizar las mismas queries para todos los arboles de
      // una misma mida para disminuir la varianza
      vector<Point> queries = generateQueries(numQueries, k);

      for (int i = 0; i < numTrees; ++i) { //For que crea T arboles y hace la cerca de Q queries
      //La creacion de los arboles dependen de que tipo de arbol estamos tratando
        int nodesVisited = 0;
        int avgNodesVisited_per_size = 0;
                
        switch(typeOfTree){
          case 0: {
            KDTree tree(n, k);
            for (int j = 0; j < numQueries; ++j) {
              int curNodesVisited = 0;
              tree.findNearestNeighbor(queries[j], curNodesVisited);
              nodesVisited += curNodesVisited;
            }
            break;
          }
          case 1: {
            RelaxedKDTree tree(n, k);
            for (int j = 0; j < numQueries; ++j) {
              int curNodesVisited = 0;
              tree.findNearestNeighbor(queries[j], curNodesVisited);
              nodesVisited += curNodesVisited;
            }
            break;
          }
          case 2: {
            SquarishKDTree tree(n, k);
            for (int j = 0; j < numQueries; ++j) {
              int curNodesVisited = 0;
              tree.findNearestNeighbor(queries[j], curNodesVisited);
              nodesVisited += curNodesVisited;
            }
            break;
          }
          default:{
            cerr << "Error: type of tree not valid" << endl;
            return 0;
          }
        }
        //Para cada arbol tratado, queremos saber la media de nodos visitados en los Q queries
        //Esto lo usaremos para calcular la MEDIA de medias de los T arboles y para
        avgNodesVisited_per_size = nodesVisited / numQueries;
        outputFile << avgNodesVisited_per_size << ' ';
      }
        //Delimita las diferentes midas que van a tener los arboles
        outputFile << endl;
    }
    //Delimita los diferentes tipos de arboles implementados
    outputFile << endl;
  }
  outputFile.close();
}
