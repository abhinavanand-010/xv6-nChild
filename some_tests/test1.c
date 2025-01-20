#include<stdio.h>
#include<unistd.h>
#include<syscall.h>

int main()
{
	nchild(6);
	printf("Hi");
	return 0;
}
