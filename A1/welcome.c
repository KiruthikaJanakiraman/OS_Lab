#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	int pid;
	printf("Welcome\n");
	pid = fork();
	if(pid == 0)
	{
		exit(1);
		printf("child\n");
		printf("%d\n",j);
	}
	else if(pid > 0)
	{		
		printf("parent\n");
	}
	else if(pid < 0)
		printf("Failure\n");
	printf("let us start learning\n");

}
