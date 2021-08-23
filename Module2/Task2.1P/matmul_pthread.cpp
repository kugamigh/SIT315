#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <pthread.h>

using namespace std::chrono;
using namespace std;

#define NUM_THREADS 10
#define SIZE 100

struct MultiplyTask
{
    int **matA, **matB, **matC;
    int start;
    int end;
};

void RandomMatrix(int **mat, int maxValue)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            mat[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
            {
                mat[i][j] += rand() % maxValue;
            }
        }
    }
}

void *MultiplyMatrix(void *arg)
{
    MultiplyTask *task = (struct MultiplyTask *)arg;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            task->matC[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
            {
                task->matC[i][j] += (task->matA[i][k] * task->matB[k][j]);
            }
        }
    }
}

void PrintMatrix(int **mat)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << mat[i][j] << ' ';
        }
        cout << endl;
    }
}

int main()
{
    pthread_t threads[NUM_THREADS];

    int **matA = (int **)malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++)
    {
        matA[i] = (int *)malloc(SIZE * sizeof(int));
    }
    int **matB = (int **)malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++)
    {
        matB[i] = (int *)malloc(SIZE * sizeof(int));
    }
    int **matC = (int **)malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++)
    {
        matC[i] = (int *)malloc(SIZE * sizeof(int));
    }

    srand(time(0));

    // Fill matrices
    RandomMatrix(matA, 2);
    RandomMatrix(matB, 2);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < SIZE; k++)
            {
                matC[i][j] += 0;
            }
        }
    }

    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < NUM_THREADS; i++)
    {
        struct MultiplyTask *task = (struct MultiplyTask *)malloc(sizeof(struct MultiplyTask));
        task->matA = matA;
        task->matB = matB;
        task->matC = matC;
        task->start = SIZE / NUM_THREADS * i;
        //condition ? yes : no
        task->end = i == NUM_THREADS - 1 ? SIZE : (SIZE / NUM_THREADS * (i + 1));

        pthread_create(&threads[i], NULL, MultiplyMatrix, (void *)task);
    }

    for (size_t i = 0; i < NUM_THREADS; i++)
    {
        (void)pthread_join(threads[i], NULL);
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
