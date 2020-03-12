#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
	int pid,j;
	printf("Welcome\n");
	pid = fork();
	if(pid == 0)
	{
		printf("%d\n",j);
		printf("child\n");
		printf("%d\n%d\n",getpid(),getppid());
	}
	else if(pid > 0)
	{
		wait(&pid);
		scanf("%d",&j);
		printf("parent\n");
		sleep(1);
		printf("%d\n%d\n",getpid(),getppid());
	}
	else if(pid < 0)
		printf("Failure\n");
	execl("/bin/ls","/bin/ls",NULL);
	printf("%d\n",j);
	printf("let us start learning\n");

}
