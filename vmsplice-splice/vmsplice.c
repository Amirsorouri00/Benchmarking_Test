#define _GNU_SOURCE
#include <sys/uio.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

ssize_t vmsplice_transfer(int pipe_out, char* data, size_t length);

int main(int argc, char *argv[]) {
    struct iovec local; 
    int fd2 = open("../../random-files/20m-files/file.txt", O_RDONLY);
    char buf[1000]; 

    unsigned long nr_segs = 500;

    local.iov_base = buf;//(void *)0x10000; 
    local.iov_len = 500;

    mkfifo("/tmp/myfifo", S_IRWXU);

    // ssize_t nread = vmsplice(fd2, &local, nr_segs, SPLICE_F_MORE);
    ssize_t nread = vmsplice_transfer(&local, fd2, nr_segs);

    if (-1 == nread) {
        printf("errno = %d\n", errno);
        perror("vmsplice");
        return 1;
    }
    return 0;
}


// data is aligned to page boundaries,
// and length is a multiple of the page size
ssize_t vmsplice_transfer(int pipe_out, char* data, size_t length)
{
    ssize_t offset = 0;
    while (offset < length) {
        struct iovec iov = { data + offset, length - offset };
        offset += vmsplice(pipe_out, &iov, 1, SPLICE_F_GIFT);
        if (offset == -1)
            return -1;
    }
    return offset;
}


