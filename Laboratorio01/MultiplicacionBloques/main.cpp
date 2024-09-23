#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <time.h>
#include <vector>  
#include <x86intrin.h>

using namespace std;
const double FRECUENCIA_CPU_MHZ = 3900.0;

void llenarMatrizAletoriamnte(vector<vector<int>>& matriz, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = rand() % n;
        }
    }
}

void multiplicacionMatricesBloques(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& resultado, int n, int tamBloque)
{
    for (int i = 0; i < n; i += tamBloque) {
        for (int j = 0; j < n; j += tamBloque) {
            for (int k = 0; k < n; k += tamBloque) {
                // Multiplicación de bloques
                for (int ii = i; ii < min(i + tamBloque, n); ++ii) {
                    for (int jj = j; jj < min(j + tamBloque, n); ++jj) {
                        int suma = 0;
                        for (int kk = k; kk < min(k + tamBloque, n); ++kk) {
                            suma += a[ii][kk] * b[kk][jj];
                        }
                        resultado[ii][jj] += suma;
                    }
                }
            }
        }
    }
}

inline uint64_t leerContadorCiclos(){
    return __rdtsc();
}

double convertirCiclosAMilisegundos(uint64_t ciclos) {
    return (ciclos / FRECUENCIA_CPU_MHZ) / 1000.0;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    int nRep = 10;
    int tamBloque = 128; // Tamaño del bloque ajustable

    for (int i = 100; i < 1000; i += 100) { // Tamaño de la matriz
        vector<vector<int>> matriz1(i, vector<int>(i));
        vector<vector<int>> matriz2(i, vector<int>(i));
        llenarMatrizAletoriamnte(matriz1, i);
        llenarMatrizAletoriamnte(matriz2, i);

        uint64_t promRep = 0;

        for (int j = 0; j < nRep; j++) {
            vector<vector<int>> MatrizResultado(i, vector<int>(i, 0)); // Inicializar en cero

            uint64_t start = leerContadorCiclos();
            multiplicacionMatricesBloques(matriz1, matriz2, MatrizResultado, i, tamBloque);
            uint64_t end = leerContadorCiclos();
            uint64_t duracionCiclos = end - start;
            promRep += duracionCiclos;

            // cout << "Tiempo de ejecucion: " << duracionCiclos << " ciclos" << endl;
        }
        uint64_t promedio = promRep / nRep;
        double duracionMiliSegundos = convertirCiclosAMilisegundos(promedio);
        cout << "El tiempo promedio para matrices de " << i << " tamaño es de " << duracionMiliSegundos << " milisegundos" << endl;
    }

    return 0;
}
// valgrind --tool=cachegrind ./
