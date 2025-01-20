#include "stdio.h"
#include "types.h"
#include "syscall.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

//int sys_nchildren(void);

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


// return value for our created system call
int
sys_nchild(void)
{
    int n;
    if (argint(0, &n) < 0) 	// take integer as command line argumnent and check if n is a positive integer.
    {
        return -1;	// if it is negative, return -1 to terminate the call.
    }
    return n;	// retruns n to the user program for further execution.
}

/*
// giving second try to the system call
void
nchildren(void)
{
    int n;

    if (argint(0, &n) < 0)
        return;

    int pid = fork_n(n);
    if (pid < 0) {
        // Error occurred
        printf(1, "Error creating child processes\n");
    } else if (pid > 0) {
        // Parent process
        printf(1, "Parent PID: %d\n", getpid());
    }
    // Child processes will print their PIDs in the fork_n function
}

*/
