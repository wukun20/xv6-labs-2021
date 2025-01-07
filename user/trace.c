#include "user/user.h"

int main(int argc, char *argv[]) {
  char **newArgv;
  newArgv = &argv[2];
  trace(atoi(argv[1]));
  if(exec(newArgv[0], newArgv) < 0) {
    printf("No program named %s\n", newArgv[0]);
  }
  exit(0);
}
