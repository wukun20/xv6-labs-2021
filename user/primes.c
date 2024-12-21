#include "user/user.h"
#define MAX 35

void prime(int nums[], int n) {
    int pid;
    int fd[2];
    if(n == 0) {
        return;
    }
    
    if(pipe(fd) < 0) {
        printf("pipe failed.\n");
        exit(1);
    }
    
    if((pid = fork()) == 0) {
        n = 0;
        close(fd[1]);
        while(read(fd[0], &nums[n], sizeof(int)) > 0) {
            ++n;
        }
        close(fd[0]);
        int newNums[n];
        memcpy(newNums, nums, n * sizeof(int));
        prime(newNums, n);
        
        
    } else {
        int x = nums[0]; // find the first num to be prime
        printf("prime %d\n", x);
        close(fd[0]);
        for(int i = 1; i < n; i++) {
            if(nums[i] % x != 0) {
                write(fd[1], &nums[i], sizeof(int));
            }
        }
        close(fd[1]);
        wait(0); // wait util all sons out, if not the memory used by suns will be reused by other
    }
    return;
}

int main(int argc, char **argv) {
    int nums[MAX-1];
    for(int i = 2; i <= MAX; i++) {
        nums[i-2] = i;
    }
    prime(nums, MAX-1);
    exit(0);
}


