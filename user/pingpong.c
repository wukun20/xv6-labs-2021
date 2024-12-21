#include "user/user.h"

int main(int argc, char **argv) {
    int fd1[2]; // [0] for child read, [1] for father write
    int fd2[2]; // [0] for father read, [1] for child write
    if(pipe(fd1) < 0 || pipe(fd2) < 0) {
        printf("pipe failed.");
        exit(1);
    }
    int pid;
    
    char buf[5];
    
    if((pid = fork()) == 0) {
        close(fd1[1]);
        close(fd2[0]);

	read(fd1[0], buf, 4);
	printf("%d: received %s\n", getpid(), buf);
        write(fd2[1], "pong", 4);
        
        close(fd1[0]);
        close(fd2[1]);
    } else {
    	close(fd1[0]);
        close(fd2[1]);
        
        write(fd1[1], "ping", 4);
        read(fd2[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        
        close(fd1[1]);
        close(fd2[0]);
    }
    
    exit(0);
}
