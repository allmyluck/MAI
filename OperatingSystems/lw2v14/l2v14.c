#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#define eror_pipe  1
#define eror_fork  2
#define read_failed 4
#define write_failed 5
//ok

int main(void) {
    int p1[2],p2[2];
    if (pipe(p1) < 0) {
        perror("pipe_failed");
        exit(eror_pipe);
    }
    if (pipe(p2) < 0) {
        perror("pipe_failed");
        exit(eror_pipe);
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork_failed");
        exit(eror_fork);
    } else if (pid == 0) {
        double middle_str;
        close(p1[1]);
        close(p2[0]);
        while(read(p1[0], &middle_str,sizeof(double)) > 0) {
            middle_str = pow(middle_str,0.5);
            if(write(p2[1], &middle_str, sizeof(double)) < 0) {
                perror("write_failed");
                exit(write_failed);
            }
        }
        close(p1[0]);
        close(p2[1]);
    } else {
        double begin_str;
        double for_result;
        close(p1[0]);
        close(p2[1]);
        while(scanf("%lf", &begin_str) > 0) {
            if(begin_str >= 0) {
                for_result = begin_str;
                if(write(p1[1], &begin_str, sizeof(double)) < 0) {
                    perror("write_failed");
                    exit(write_failed);
                }
                if(read(p2[0], &begin_str, sizeof(double)) < 0) {
                    perror("read_failed");
                    exit(read_failed);
                }
                printf("%.3lf^(1/2) = %.3lf\n",for_result, begin_str); 
            } 
        }
        close(p2[0]);
        close(p1[1]); 
    }
    return 0;
}
