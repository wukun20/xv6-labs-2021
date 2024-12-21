#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

void find(char *path, char *filename) {
    int fd;
    struct stat st;
    struct dirent de; //include inum and name
    char newPath[512], *p;
    if((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(newPath)){
      	printf("ls: path too long\n");
        return;
    }
    
    strcpy(newPath, path);
    p = newPath + strlen(newPath);
    *p++ = '/';
    p[DIRSIZ] = '\0';
    
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
        if(de.inum == 0 || !strcmp(de.name, ".") || !strcmp(de.name, "..")) {
            continue;
       }

        memmove(p, de.name, DIRSIZ);
        
        if(stat(newPath, &st) < 0){
            fprintf(2, "find: cannot stat %s\n", path);
            close(fd);
            return;
        }
        switch(st.type) {
            case T_FILE:
                if(!strcmp(de.name, filename)) {
                    printf("%s\n",newPath);
                }
                break;
            case T_DIR:
                find(newPath, filename);
        }      
    }
    close(fd);
    
} 

int main(int argc, char *argv[]) {
    if(argc > 3) {
        fprintf(2, "find: find <path> <filename>\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}



