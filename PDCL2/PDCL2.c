#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int **M1, **M2, **M3;

// Function to allocate memory for matrices
void allocateMemory() {
    M1 = (int **)malloc(N * sizeof(int *));
    M2 = (int **)malloc(N * sizeof(int *));
    M3 = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        M1[i] = (int *)malloc(N * sizeof(int));
        M2[i] = (int *)malloc(N * sizeof(int));
        M3[i] = (int *)malloc(N * sizeof(int));
    }
}

// Function to initialize matrices with random values
void initialize() {
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            M1[i][j] = rand() % 100;
            M2[i][j] = rand() % 100;
        }
}

void addRowMajor() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            M3[i][j] = M1[i][j] + M2[i][j];
}

void addColumnMajor() {
    for (int j = 0; j < N; j++)
        for (int i = 0; i < N; i++)
            M3[i][j] = M1[i][j] + M2[i][j];
}

void directAddition() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            M3[i][j] = M1[i][j] + M2[i][j];
}

void freeMemory() {
    for (int i = 0; i < N; i++) {
        free(M1[i]);
        free(M2[i]);
        free(M3[i]);
    }
    free(M1);
    free(M2);
    free(M3);
}

int main() {
    allocateMemory();
    initialize();

    clock_t start, end;

    start = clock();
    addRowMajor();
    end = clock();
    printf("Row Major Execution Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    addColumnMajor();
    end = clock();
    printf("Column Major Execution Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    directAddition();
    end = clock();
    printf("Direct Addition Execution Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    freeMemory();
    return 0;
}
