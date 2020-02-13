#include <sys/ipc.h>
# define NULL 0 
#include <sys/shm.h> 
#include <sys/types.h> 
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<string.h> 
# include<ctype.h>
# include<sys/wait.h> 
//#include <stdio_ext.h>
// parent writing a char in shared memory and child reads it and prints it.
int main()
{
	int pid;
	char *a,*b,c;
	int id,n,i;
	// you can create a shared memory between parent an d child 	here or you can create inside them separately.
	id=shmget(111,50,IPC_CREAT | 00666); 
	pid=fork();
	if(pid>0)
	{
		// id=shmget(111,50,IPC_CREAT | 00666);
		a=shmat(id,NULL,0);
		printf("Parent process:\n");
		printf("Enter a string: ");
		scanf(" %[^\n]",a);
		wait(NULL); 
		shmdt(a);
	}
	else
	{
		sleep(3); 
		//id=shmget(111,50,0); 
		b=shmat(id,NULL,0);
		int i=0;
		while(b[i]!='\0')
		{
			b[i]=toupper(b[i]);
			i++;
		}
		printf("\nChild process:\n");
		printf("%s\n",b); 
		shmdt(b);
	}
	shmctl(id, IPC_RMID,NULL);
}
