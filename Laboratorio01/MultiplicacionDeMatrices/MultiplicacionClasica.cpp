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

void multiplicacionMatrices(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& resultado, int n)
{
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            resultado[j][i] = 0;
            for (int e = 0; e < n; ++e) {
                resultado[j][i] += a[j][e] * b[e][i];
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
    int nRep = 2;
    for (int i = 100; i < 1000; i = i+100 ){ //tamaño de la matriz
        vector<vector<int>> matriz1(i, vector<int>(i));
        vector<vector<int>> matriz2(i, vector<int>(i));
        llenarMatrizAletoriamnte(matriz1, i);
        llenarMatrizAletoriamnte(matriz2, i);

        uint64_t promRep = 0;

        for(int j = 0; j < nRep; j++){
            vector<vector<int>> MatrizResultado(i, vector<int>(i));

            uint64_t start = leerContadorCiclos();
            multiplicacionMatrices(matriz1, matriz2, MatrizResultado, i);
            uint64_t end = leerContadorCiclos();
            uint64_t duracionCiclos = end - start;
            promRep += duracionCiclos;

            //cout << "Tiempo de ejecucion: " << duracionCiclos << " ciclos" << endl;
        }
        uint64_t promedio = promRep/nRep;
        double duracionMiliSegundos = convertirCiclosAMilisegundos(promedio);
        cout << "El tiempo promedio para matrices de " << i << " tamanio es de " << duracionMiliSegundos << " milisegundos" << endl;
    }
             
    

    return 0;
}
//valgrind --tool=cachegrind ./
//kcachegrind cachegrind.out.