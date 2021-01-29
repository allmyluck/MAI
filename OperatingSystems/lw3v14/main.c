#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mcheck.h>
#include <stdio.h>
#define max_thr 8949


typedef struct{
	double** array;
	int number_str;
	int position;
    int size_m;
} pthrData;


bool swap(pthrData *data) {
    if(data->array[data->number_str][data->number_str] == 0) {
        int i = data->number_str;
        while(i < data->size_m) {
            if(data->array[i][data->number_str] != 0) {
                double v;
                for(int index = data->number_str; index < data->size_m; index++) {
                    v = data->array[i][index];
                    data->array[i][index] = data->array[data->number_str][index];
                    data->array[data->number_str][index] = v;  
                }
                return true;
            }
        i++;
        }
    } else {
        return true;
    }
    return false;
}


pthrData get_new_data(pthrData *data,int j) {
    pthrData new_data;
    new_data.array = data->array;
	new_data.number_str = data->number_str;
	new_data.position = j;
    new_data.size_m = data->size_m;
	return new_data;
}


void* Operation(void* thread_data){
	pthrData *data = (pthrData*)thread_data;
    if(data->position >= data->size_m) {
        return NULL;
    }
    double x = -1 * data->array[data->position][data->number_str] / data->array[data->number_str][data->number_str];
    for(int index = data->number_str;index < data->size_m; index++) {
        data->array[data->position][index] = data->array[data->position][index] + x * data->array[data->number_str][index];
    }
    return NULL;
}


int main(int argc, char **argv){
	if (argc != 2) {
		printf("Error\n");
		return 0;
	}
	int n = atoi(argv[1]);
	int size;
	scanf("%d", &size);
	if(n > max_thr) {
		printf("max of threads = 8949\n");
		n = max_thr;
    }
	double **matrix = (double **)malloc(sizeof(double *) * size);
	for(int i = 0; i < size; i++) {
		matrix[i] = (double *)malloc(sizeof(double) * size);
	}
	for(int i = 0; i < size; i++){ 
		for(int j = 0; j < size; j++){
			double value;
			scanf("%lf", &value);
			matrix[i][j] = value;
		}
	}
    pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * n);
	pthrData* threadData = (pthrData*)malloc(sizeof(pthrData));
	threadData->array = matrix;
	threadData->number_str = 0;
	threadData->position = 0;
    threadData->size_m = size;
    int size_of_amount = size;
    bool ind = true;
    int amount_thr = 0;
    while(size_of_amount > 1) {
        if(swap(threadData) == false) {
            ind = false;
            printf("Determinant = 0\n");
            break;
        }
        if(n >= size_of_amount - 1) {
            pthrData* new_data = (pthrData*)malloc(sizeof(pthrData) * size_of_amount - 1);
            for(int index = threadData->position + 1; index < size; index++) {
                new_data[amount_thr] = get_new_data(threadData,index);
                pthread_create(&threads[amount_thr], NULL, Operation, &new_data[amount_thr]);
                amount_thr++;
            }
            for(int index = 0; index < amount_thr; index++) {
                pthread_join(threads[index], NULL);
            }
            amount_thr = 0;
            free(new_data);
        } else if(n < size_of_amount - 1) {
            bool indicator = true;
            int count_n = threadData->position + 1;
            int limit = count_n + n;
            pthrData* new_data = (pthrData*)malloc(sizeof(pthrData) * n);
            while(indicator == true) {
                if(limit >= size) {
                    indicator = false;
                }
                for(int index = count_n; index < limit; index++) {
                    new_data[amount_thr] = get_new_data(threadData,index);
                    pthread_create(&threads[amount_thr], NULL, Operation, &new_data[amount_thr]);
                    amount_thr++;
                }
                for(int index = 0; index < amount_thr; index++) {
                    pthread_join(threads[index], NULL);
                }
                amount_thr = 0;
                count_n = limit;
                limit = limit + n;
            }
            free(new_data);
        }
        threadData->position++;
        threadData->number_str++;
        size_of_amount--;
    }
    if(ind == true) {
        double det = 1;
        for(int index = 0; index < threadData->size_m; index++) {
            if(threadData->array[index][index] == 0) {
                det = 0;
                break;
            }
            det = det * threadData->array[index][index];
        }
        printf("Determinant = %.1lf\n", det);
    }
	free(threads);
	for(int i = 0; i < size; i++){
		free(matrix[i]);
	}
	free(matrix);
	free(threadData);
	return 0;
}
