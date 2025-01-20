#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(1, "Usage: %s <n>\n", argv[0]);
        exit();
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf(1, "Invalid value for n\n");
        exit();
    }

    printf(1, "Creating %d child processes...\n", n);
    fork_n(n);

    exit();
}

