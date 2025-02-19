#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

    // A1 = A2+A3
    typedef struct {
        int *a1;
        int *a2;
        int *a3;
        int start;
        int end;
    } partialData;

    clock_t startTime, endTime;
    double timeElapsed;



void arrShow(int *arr, int start, int end) {
        printf("\n Array: ");
    // for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
    for (int i = start; i < end; i++) {
        printf(" %d ", arr[i]);
    }
    printf("\n");
}

void *getSum(void *arg) {
    partialData *part = (partialData *)arg;
    
    // printf("\n");
    for (int i = part->start; i < part->end; i++) {
        part->a1[i] = part->a2[i] + part->a3[i];
        // printf("%d ", part->a1[i]);
        // printf("SUM: %d = %d + %d \n", part->a1[i], part->a2[i], part->a3[i]);
    }
    // printf("\n");
    // arrShow(part->a1, part->start, part->end);
    pthread_exit(NULL);
}

void populateArray(int *arr, int sizeArray) {
    srand(time(NULL));
    for (int i = 0; i < sizeArray; i++) {
        arr[i] = rand() % 100;
    }
}

int main() { 
    int sizeArray;
    int numThreads;

    int threads[] = {1, 5, 10, 15, 20, 25, 30};
    int arraysz[] = {50000, 100000, 150000, 200000, 250000, 300000, 350000,400000};

    // int threads[] = {1};
    // int arraysz[] = {10};

    for (int thread = 0; thread < (sizeof(threads)/sizeof(threads[0])); thread++) {
        for (int arrayCurr = 0; arrayCurr < (sizeof(arraysz)/sizeof(arraysz[0])); arrayCurr++) {
            // printf("Enter total Array Size:  ");
            // scanf("%d", &sizeArray);
            // printf("Enter number of threads: ");
            // scanf("%d", &numThreads);

            // Getting current values for array/threads
            sizeArray = arraysz[arrayCurr];
            numThreads = threads[thread];
            int sizeChunk = sizeArray/numThreads;

            // Making arrays for the numbers, threads and arguements
            // This can be improved by making an array for these
            int *a1 = (int *)malloc(sizeArray * sizeof(int));
            int *a2 = (int *)malloc(sizeArray * sizeof(int));
            int *a3 = (int *)malloc(sizeArray * sizeof(int));
            pthread_t threads[numThreads];  
            partialData part[numThreads];

            // Populating the number vectors
            populateArray(a2, sizeArray);
            populateArray(a3, sizeArray);


            // Making threads and passing partial data to threads
            for (int i = 0; i < numThreads; i++) {
                part[i].a1 = a1;
                part[i].a2 = a2;
                part[i].a3 = a3;
                part[i].start = i * sizeChunk;
                part[i].end = (i == numThreads - 1) ? sizeArray : (i + 1) * sizeChunk;

                // Threads launched
                pthread_create(&threads[i], NULL, getSum, &part[i]);
            }

            startTime = clock();

            // Joining threads to get output and make sure they end before proceeding further
            for (int i = 0; i < numThreads; i++) {
                pthread_join(threads[i], NULL);
            }

            endTime = clock();

            printf("Array %d \nThreads: %d \n", sizeArray, numThreads);
            timeElapsed = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            printf("Execution Time: %f seconds\n\n", timeElapsed);

            free(a1);
            free(a2);
            free(a3);

        }
    }

    return 0;
}
