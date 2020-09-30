#include <apue.h>
#include <errno.h>

#include <fcntl.h>

#define READ_BUFFER_SIZE 4096

const char buf[] = "abcdefghij";

int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        err_quit("usage:file_IO <dirname>");
    }

    int fd;
    if ((fd = open(argv[1], O_RDWR|O_APPEND|O_CREAT|O_EXCL|O_TRUNC)) < 0)
    {
        err_sys("open error");
    }
    
    if (write(fd, buf, 10) != 10)
    {
        err_sys("buf write error");
    }

    printf("read file:%s on flag O_APPEND:\n", argv[1]);

    char read_buf[READ_BUFFER_SIZE];
    if (read(fd, read_buf, READ_BUFFER_SIZE) > 0)
    {
        printf("%s", read_buf);
    }

    printf("\n");
    printf("read file:%s after lseek 0:\n", argv[1]);
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        err_sys("lseek error");
    }
    read_buf[0] = 0;
    if (read(fd, read_buf, READ_BUFFER_SIZE) > 0)
    {
        printf("%s", read_buf);
    }
    
    printf("\n");
    printf("write file:%s after lseek 0:\n", argv[1]);
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        err_sys("lseek error");
    }
    if (write(fd, buf, 10) != 10)
    {
        err_sys("buf write error");
    }
    
    printf("\n");
    printf("read file:%s \n", argv[1]);
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        err_sys("lseek error");
    }
    read_buf[0] = 0;
    if (read(fd, read_buf, READ_BUFFER_SIZE) > 0)
    {
        printf("%s", read_buf);
    }
    printf("\n");

    exit(0);
}