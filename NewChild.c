#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    printf(2, "Usage: NewChild <number of child processes>\n");
    exit();
  }

  int n = atoi(argv[1]);
  int pids[n];
  printf(1, "Creating %d child processes\n", n);
  int ret = mchild(n, pids);
  if (ret == 0) {
    printf(1, "Successfully created %d child processes\n", n);
    for (int i = 0; i < n; i++) {
      printf(1, "Child process %d has PID %d\n", i + 1, pids[i]);
    }
  } else {
    printf(2, "Error creating child processes\n");
  }

  exit();
}
