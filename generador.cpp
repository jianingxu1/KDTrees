#include <iostream>
#include <fstream>
#include <random>

using namespace std;


/*GENERADOR QUE DADO n NODOS, CADA UNO DE k VALORES, NOS GENERA UN FICHERO CON nxk VALORES DISTRIBUIDOS UNIFORMEMENTE ENTRE
0.f y 1.0f */

int main() {
    int N; // Número de filas (nodos)
    int K; // Número de columnas (valores por nodo)
    string filename; // Nombre del archivo de salida

    cout << "Ingrese el número de nodos (N): ";
    cin >> N;

    cout << "Ingrese el número de valores por nodo (K): ";
    cin >> K;

    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> filename;

    // Generador de números aleatorios uniformes entre 0 y 1
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 1.0f);

    // Abre el archivo para escritura
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Genera y escribe los valores en el archivo
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            float value = dis(gen);
            outFile << value << " ";
        }
        outFile << "\n"; // Nueva línea para cada nodo --> lo podemos quitar si da problemas
    }

    // Cierra el archivo
    outFile.close();

    cout << "Valores generados y guardados en '" << filename << "'." << endl;

    return 0;
}
