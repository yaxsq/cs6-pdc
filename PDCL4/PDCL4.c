#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

typedef struct {
    int *v1;
    int *v2;
    int start;
    int end;
} partialData;

clock_t startTime, endTime;
double timeElapsed;

long long dotProduct = 0;        // Global variable for the result
pthread_mutex_t mutex;           // Mutex for locking

// Array to store results to write in a file
#define MAX_RESULTS 50
char results[MAX_RESULTS][100];
int resultIndex = 0;

void arrShow(int *arr, int start, int end) {
        printf("\n Array: ");
    // for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
    for (int i = start; i < end; i++) {
        printf(" %d ", arr[i]);
    }
    printf("\n");
}

void *getDotProduct(void *arg) {
    partialData *part = (partialData *)arg;
    long long localSum = 0;
    // printf("\n");
    for (int i = part->start; i < part->end; i++) {
        localSum = part->v1[i] * part->v2[i];
        // printf("%d ", part->a1[i]);
        // printf("SUM: %d = %d + %d \n", part->a1[i], part->a2[i], part->a3[i]);
    }
    // printf("\n");
    // arrShow(part->a1, part->start, part->end);

    pthread_mutex_lock(&mutex);
    dotProduct += localSum;
    pthread_mutex_unlock(&mutex);


    pthread_exit(NULL);
}

void populateArray(int *arr, int sizeArray) {
    srand(time(NULL));
    for (int i = 0; i < sizeArray; i++) {
        arr[i] = rand() % 100;
    }
}

void writeResults() {
    FILE *file = fopen("results.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < resultIndex; i++) {
        fprintf(file, "%s\n", results[i]);
    }

    fclose(file);
    printf("Results written to results.txt\n");
}

int main() { 
    int sizeArray;
    int numThreads;

    int threads[] = {1, 5, 10, 15, 20, 25, 30};
    int arraysz[] = {50000, 100000, 150000, 200000, 250000, 300000, 350000,400000};

    // int threads[] = {1};
    // int arraysz[] = {10};

    for (int thread = 0; thread < (sizeof(threads)/sizeof(threads[0])); thread++) {

        char line[500] = ""; // Stores one line of results
        
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
            int *v1 = (int *)malloc(sizeArray * sizeof(int));
            int *v2 = (int *)malloc(sizeArray * sizeof(int));
            pthread_t threads[numThreads];  
            partialData part[numThreads];

            // Populating the vectors
            populateArray(v1, sizeArray);
            populateArray(v2, sizeArray);

            dotProduct = 0;

            // Making threads and passing partial data to threads
            for (int i = 0; i < numThreads; i++) {
                part[i].v1 = v1;
                part[i].v2 = v2;
                part[i].start = i * sizeChunk;
                part[i].end = (i == numThreads - 1) ? sizeArray : (i + 1) * sizeChunk;

                // Threads launched
                pthread_create(&threads[i], NULL, getDotProduct, &part[i]);
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

            char temp[50];
            snprintf(temp, sizeof(temp), "%.6f/%d ", timeElapsed, sizeArray);
            strcat(line, temp);

            free(v1);
            free(v2);

        }

        snprintf(results[resultIndex], sizeof(results[resultIndex]), "%s", line);
        resultIndex++;

    }

    writeResults();
    pthread_mutex_destroy(&mutex);

    return 0;
}
