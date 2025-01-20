#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(2, "Usage: %s <number of child processes>\n", argv[0]);	// to ensure if the command line arguments are properly fed.
        exit();
    }

    int n = atoi(argv[1]);	// reads the command line input from bash
    int result = nchild(n);	// function invoked written in  sysproc.c to return n and stored in result
    for (int i = 0; i < result; i++) {
        
            printf(1, "Child process %d with PID %d\n", i + 1,i+1 /* getpid()*/);	// return child process number with their processID in xv6
            exit();
        
    }

    for (int i = 0; i < result; i++) 	// system put on waiting till the child is created(usually to ignore the zombie processes)
    {
        wait();
    }

    exit();
}

