#define _GNU_SOURCE
#include <sys/uio.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int filelen = 2048;

int main(int argc, char *argv[]){
    // struct iovec local; 
    // local.iov_base = buf;//(void *)0x10000; 
    // local.iov_len = 500;
    unsigned long cnt = 0;
    do{
        /* 
         * tee stdin to stdout
         */
        int len = tee(STDIN_FILENO, STDOUT_FILENO, filelen, SPLICE_F_NONBLOCK);
        filelen -= len;
        if (len < 0){
            // printf("%d", len);
            if(errno == EAGAIN)
                continue;
            perror("tee");
            exit(EXIT_FAILURE);
        }
        else{
            if(filelen == 0 || len == 0)
                return 0;
                // break; 
            cnt += len;
            printf("\n%ld\n", cnt);
        }
    } while (1);
    
    return 0;
}