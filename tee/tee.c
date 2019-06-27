#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>


int main(int argc, char *argv[]){
    int fd, fd2;
    int len, slen;

    assert(argc == 2);
    fd = open (argv[1], O_RDONLY , 0664);
    fd2 = open (argv[2], O_WRONLY |O_CREAT|O_TRUNC, 0664);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    do{
        /* 
         * tee stdin to stdout
         */
        len = tee(STDIN_FILENO, STDOUT_FILENO, INT_MAX, SPLICE_F_NONBLOCK);
        if(len == 0)
            break;
        else if (len < 0){
            if(errno == EAGAIN)
                continue;
            perror("tee");
            exit(EXIT_FAILURE);
        }

    } while (1);
    close(fd);
    exit(EXIT_SUCCESS);
}
