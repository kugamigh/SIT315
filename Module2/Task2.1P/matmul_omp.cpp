#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <omp.h>

using namespace std::chrono;
using namespace std;

#define SIZE 100

void RandomMatrix(int **mat, int maxValue) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                mat[i][j] += rand() % maxValue;
            }
        }
    }
}


void MultiplyMatrix(int **matA, int **matB, int **matC) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matC[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                matC[i][j] += (matA[i][k] * matB[k][j]);
            }
        }
    }
}

void PrintMatrix(int **mat) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << mat[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    int num_threads = 64;
    int **matA = (int **) malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        matA[i] = (int *) malloc(SIZE * sizeof(int));
    }
    int **matB = (int **) malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        matB[i] = (int *) malloc(SIZE * sizeof(int));
    }
    int **matC = (int **) malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        matC[i] = (int *) malloc(SIZE * sizeof(int));
    }

    omp_set_num_threads(num_threads);
    srand(time(0));

    // Fill matrices
    RandomMatrix(matA, 2);
    RandomMatrix(matB, 2);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                matC[i][j] += 0;
            }
        }
    }

    auto start = high_resolution_clock::now();

    #pragma omp parallel default(none) firstprivate(matA, matB, matC)
    {
        int thread_id = omp_get_thread_num();

        #pragma omp for schedule(static)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matC[i][j] = 0;
                for (int k = 0; k < SIZE; k++) {
                    matC[i][j] += (matA[i][k] * matB[k][j]);
                }
            }
        }
    }


    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    // cout << "Printing matA" << endl;
    // PrintMatrix(matA);

    // cout << "Printing matB" << endl;
    // PrintMatrix(matB);
    
    // cout << "Printing matC" << endl;
    // PrintMatrix(matC);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}
