#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#define MAX 100
using namespace std;
using namespace std::chrono;

void llenarMatrizAletoriamnte(int matriz[MAX][MAX])
{
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matriz[i][j] = rand() % 100;
        }
    }
}

void multiplicacionMatrices(int a[MAX][MAX], int b[MAX][MAX], int resultado[MAX][MAX])
{
    for (int j = 0; j < MAX; j++) {
        for (int i = 0; i < MAX; i++) {
            resultado[j][i] = 0;
            for (int e = 0; e < MAX; ++e) {
                resultado[j][i] += a[j][e] * b[e][i];
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    int matriz1[MAX][MAX];
    int matriz2[MAX][MAX];
    int MatrizResultado[MAX][MAX];

    llenarMatrizAletoriamnte(matriz1);
    llenarMatrizAletoriamnte(matriz2);

    auto start = high_resolution_clock::now();

    multiplicacionMatrices(matriz1, matriz2, MatrizResultado);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    cout << "Tiempo de ejecucion: " << duration << " milisegundos" << endl;

    return 0;
}
//valgrind --tool=cachegrind ./
//kcachegrind cachegrind.out.