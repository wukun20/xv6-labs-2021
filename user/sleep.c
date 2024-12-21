#include "user/user.h"
int main(int argc, char** argv) {
    if(argc != 2) {
        printf("please pass one argument.\n");
        exit(1);
    }
    int tick_num = atoi(argv[1]);
    int sleep_num = sleep(tick_num);
    
    exit(sleep_num == tick_num ? 0 : 1);
}
