#include <stdio.h>
#include<string.h>
#include "user.h"

int main() {
  int numChildren = 5;
  int result = nchildren(numChildren);
  if (result == 0) {
    printf(1,"Created %d children\n", numChildren);
  } else {
    printf(2,"Failed to create children\n");
  }
  return 0;
}

