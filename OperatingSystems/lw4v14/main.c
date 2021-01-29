#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#define mmap_error 1
#define fork_error  2
#define semaphores_error 3
#define mkstemp_failed 4
#define write_failed 5
#define munmap_failed 6


int get_file()
{
	char *t_f = strdup("/tmp/t_f.XXXXXX");//временная папка tmp
	int fd = mkstemp(t_f);//создает временный файл
	if(fd == -1) {
		perror("mkstemp_failed");
		exit(mkstemp_failed);
	}
	unlink(t_f);
	free(t_f);
	if(write(fd, "_gg_", 4) < 0) {
		perror("write_failed");
		exit(write_failed);
	}
	return fd;
}


int main(void) {
    int fd = get_file();
	unsigned char* memory = (unsigned char*)mmap(NULL, 4, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);//разделен с другими процессами
	if (memory == MAP_FAILED) {
		perror("mmap_failed");
		exit(mmap_error);
	}
	sem_t* get_sqrt = sem_open("get_sqrt", O_CREAT, 777, 0);
	sem_t* output = sem_open("output", O_CREAT, 777, 0);
	if (get_sqrt == SEM_FAILED || output == SEM_FAILED) {
		perror("Semaphores doesn't create");
		exit(semaphores_error);
	}
	sem_unlink("get_sqrt");//реальное удаление семафора не будет осуществлено до тех пор, пока он не будет окончательно закрыт.
	sem_unlink("output");
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork_failed");
        exit(fork_error);
    } else if (pid > 0) {
        double begin_str,result;
        while(scanf("%lf", &begin_str) > 0) {
            double* set = (double*)((unsigned char *)(memory) + 0);
            *set = begin_str;
            sem_post(get_sqrt);
			sem_wait(output);//ожидание доступа для output
            double* get = (double*)((unsigned char *)(memory) + 1);
            result = *get;
            printf("%.3lf^(1/2) = %.3lf\n",begin_str, result);

		}
		sem_close(get_sqrt);
		sem_close(output);
		close(fd);
    } else {//child prc 
        double new_str;
        while (true) {
			sem_wait(get_sqrt);//ожидание доступа для get_sqrt
            double* get = (double*)((unsigned char *)(memory) + 0);
            new_str = *get;
            new_str = pow(new_str,0.5);
            double *set = (double*)((unsigned char *)(memory) + 1);
            *set = new_str;
            sem_post(output);//разблокировка output
		}
		sem_close(get_sqrt);
		sem_close(output);
		close(fd);
    }
	if(munmap(memory, 4) == -1) {
		perror("munmap_failed");
		exit(munmap_failed);
	}
    return 0;
}