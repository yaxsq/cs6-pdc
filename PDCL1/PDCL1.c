#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

    typedef struct {
        int *chunk;
        int start;
        int end;
        long sum;
    } partialData;

    clock_t startTime, endTime;
    double timeElapsed;


void *getSum(void *arg) {
    partialData *part = (partialData *)arg;
    part->sum = 0;

    // printf("\n");
    for (int i = part->start; i < part->end; i++) {
        part->sum += part->chunk[i];
        // printf("%d ", part->chunk[i]);
    }
    // printf("\n");

    pthread_exit(NULL);
}


void populateArray(int *arr, int sizeArray) {
    srand(time(NULL));
    for (int i = 0; i < sizeArray; i++) {
        arr[i] = rand() % 100;
    }
}

int totalSum(int numThreads, partialData part[]) {
    long totalSum = 0;
    for (int i = 0; i < numThreads; i++) {
        totalSum += part[i].sum;
        // printf("Part sum %d is: %ld\n", i, part[i].sum);
    }
    return totalSum;
}

int main() { 
    int sizeArray;
    int numThreads;

    int threads[] = {1, 5, 10, 15, 20, 25, 30};
    int arraysz[] = {50000, 100000, 150000, 200000, 250000, 300000, 350000,400000};

    for (int thread = 0; thread < (sizeof(threads)/sizeof(threads[0])); thread++) {
        for (int arrayCurr = 0; arrayCurr < (sizeof(arraysz)/sizeof(arraysz[0])); arrayCurr++) {
            // printf("Enter total Array Size:  ");
            // scanf("%d", &sizeArray);
            // printf("Enter number of threads: ");
            // scanf("%d", &numThreads);

            sizeArray = arraysz[arrayCurr];
            numThreads = threads[thread];
            int sizeChunk = sizeArray/numThreads;

            // Making arrays for the numbers, threads and arguements
            int *arr = (int *)malloc(sizeArray * sizeof(int));
            pthread_t threads[numThreads];
            partialData part[numThreads];

            // Populating the number array
            populateArray(arr, sizeArray);

            startTime = clock();

            // Making threads and passing partial data to threads
            for (int i = 0; i < numThreads; i++) {
                part[i].chunk = arr;
                part[i].start = i*sizeChunk;
                if (i == numThreads-1) {
                    part[i].end = sizeArray;
                } else {
                    part[i].end = (i+1)*sizeChunk;
                }

                // Threads launched
                pthread_create(&threads[i], NULL, getSum, &part[i]);
            }

            // Joining threads to get output and make sure they end before proceeding further
            for (int i = 0; i < numThreads; i++) {
                pthread_join(threads[i], NULL);
            }

            endTime = clock();

            // Getting the total sum
            long totalSumCalculated = (long)totalSum(numThreads, part);

            printf("Array %d \nThreads: %d \n ", sizeArray, numThreads);
            printf("Total Sum is: %ld\n", totalSum);
            timeElapsed = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            printf("Execution Time: %f seconds\n\n", timeElapsed);

            free(arr);

        }
    }

    return 0;
}
