#include "user/user.h"
#include "kernel/param.h" //import MAXARG

int main(int argc, char **argv) {
    if(argc != 3) {
        fprintf(2, "Need 3 parameters.\n");
        exit(1);
    }
    char buf[MAXARG], *p;
    int pid = 0;
    char **myArgv;
    if((myArgv = malloc(3 * sizeof(char **))) == 0) {
        fprintf(2, "Malloc fail.\n");
        exit(1);
    };
    myArgv[0] = argv[1];
    myArgv[1] = argv[2];
    p = buf;
    while(p < buf + MAXARG) {
        if(read(0, p, sizeof(char)) < 0) {
            fprintf(2, "Read error.\n");
            exit(1); 
        }
        if(*p == '\0') {
            break;
        }
        if(*p == '\n') {
            *p = '\0';
            myArgv[2] = malloc((strlen(buf) + 1)* sizeof(char));
            memcpy(myArgv[2], buf, (strlen(buf) + 1) * sizeof(char));
            if((pid = fork()) == 0) {
                exec(myArgv[0], myArgv);
            }
            wait(0);
            p = buf - 1;
        }
        p++;
    }
    for(int i = 0; i < 3; i++) {
        if(myArgv[i] != 0) {
             free(myArgv[i]);
        }
    }
    free(myArgv);
    exit(0);
}
