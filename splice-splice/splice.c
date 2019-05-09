#define _GNU_SOURCE
#include <sys/uio.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>

int main(int argc, char *argv[]){
    ssize_t nread; 
    int     pfd[2];
    pid_t   childpid;
    unsigned long nr_segs = 20000000;
    
    int fd = open("../../random-files/20m-files/file.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    pipe(pfd);
    if((childpid = fork()) == -1)
    {
            perror("fork");
            exit(1);
    }

    if(childpid == 0)
    {
        /* Child process closes up input side of pipe */
        close(pfd[0]);
        nread += splice(fd, NULL, pfd[1], NULL, nr_segs, SPLICE_F_MOVE);
        exit(0);
    }
    else
    {
        /* Parent process closes up output side of pipe */
        close(pfd[1]);
        nread += splice(pfd[0], NULL, STDOUT_FILENO, NULL, nr_segs, SPLICE_F_MOVE);
        printf("Received string: %d", (int)nread);
        exit(0);
    }

    return 0;
}