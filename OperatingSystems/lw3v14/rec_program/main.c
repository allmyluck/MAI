// gcc -g main.c -o main.out -lpthread
//-v --leak-check=full ./main.out
// max threads 8949
// делаю без рекурсии цикл вайн в нем подсчет где для каждого совй индекс, swap не поточная наверное тоже она первая
#include <pthread.h>
#include <stdlib.h>
#include <mcheck.h>
#include <stdio.h>
#define max_thr 8949
#define error_thr -1
int amount_thr = 1;


int amount_threads(int size) {
	if(size <= 2) {
		return 0;
	}
	for(int i = 0; i < size;i++) {
		amount_thr++;
		amount_threads(size - 1);
	}
	return 0;
}


typedef struct{
	int** array;
	int det;
	int size_st;
	int k;
} pthrData;


pthrData get_new_data(pthrData *data,int j) {
	int a = 0, b = 0;
	pthrData new_data;
	new_data.det = 0;
	new_data.size_st =  data->size_st - 1;
	new_data.k = 1;
	new_data.array = (int **)malloc(sizeof(int *) * new_data.size_st);//указатель на массив указателей
	for(int i = 0; i < new_data.size_st; i++) {
		new_data.array[i] = (int *)malloc(sizeof(int) * new_data.size_st); //массив из указателей 
	}
	for(int i = 1; i < data->size_st; i++) {
		for(int i2 = 0; i2 < data->size_st;i2++) {
			if(i2 != j) {
				new_data.array[a][b] = data->array[i][i2];
				b++;
			}
		}
	b = 0;
	a++;
	}
	return new_data;
}


void* Determinant(void* thread_data){
	pthrData *data = (pthrData*)thread_data;
	if(data->size_st == 1) {
		data->det = data->array[0][0];
		return NULL;
	}
	if(data->size_st == 2) {
		int t = data->array[0][0] * data->array[1][1] - (data->array[0][1] * data->array[1][0]);
		data->det = data->det + t;
		return NULL;
	}
	pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * data->size_st);
	pthrData* new_data = (pthrData*)malloc(sizeof(pthrData) * data->size_st);
	for(int i = 0; i < data->size_st; i++) {
		new_data[i] = get_new_data(data,i);
		pthread_create(&threads[i], NULL, Determinant, &new_data[i]);
	}
	for(int i = 0;i < data->size_st;i++) {
		pthread_join(threads[i], NULL);
		data->det = data->det + data->k * data->array[0][i] * new_data[i].det;
		data->k = -1 * data->k;
	}
	for(int i = 0;i < data->size_st;i++) {
		for(int j = 0;j < data->size_st - 1;j++) {
			free(new_data[i].array[j]);
		}
		free(new_data[i].array);
	}
	free(threads);
	free(new_data);
	return NULL;
}
/*
!!!!!!!!!!!struct 2-massiv in computer produced
**->(*(1)->_*(2)->_*(3)->_)
			5	  1      3      
			6	  4	     4
			7	  5	     0
			8	  3	     0
			9	  1	     0
massv[1][4] = 8
*/
int main(int argc, char **argv){
	if (argc != 2) {
		printf("Error\n");
		return 0;
	}
	int n = atoi(argv[1]);
	int size,dete = 0;
	scanf("%d", &size);
	amount_threads(size);
	 if(n > max_thr) {
		printf("max of threads = 8949\n");
		exit(error_thr);
    } else if(n < amount_thr) {
		printf("By this matrix you need %d threads\n", amount_thr);
		exit(error_thr);
	}
	int **matrix = (int **)malloc(sizeof(int *) * size);
	for(int i = 0; i < size; i++) {
		matrix[i] = (int *)malloc(sizeof(int) * size);
	}
	for(int i = 0; i < size; i++){ 
		for(int j = 0; j < size; j++){
			int value;
			scanf("%d", &value);
			matrix[i][j] = value;
		}
	}
	pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t));
	pthrData* threadData = (pthrData*)malloc(sizeof(pthrData));
		threadData->array = matrix;
		threadData->size_st = size;
		threadData->det = 0;
		threadData->k = 1;
		pthread_create(threads, NULL, Determinant,threadData);
		pthread_join(*threads, NULL);
	
	printf("Determinant : %d\n", threadData->det);
	free(threads);
	for(int i = 0; i < size; i++){
		free(matrix[i]);
	}
	free(matrix);
	free(threadData);
	return 0;
}
