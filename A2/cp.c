#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <dirent.h>


int main(int argc, char *argv[])
{

	if(argc==3)
	{
		int f1 = open(argv[1],O_RDONLY);
		if(f1 == -1)
		{
			printf("File doesn't exist\n\n");
			return 0;
		}

		int f2 = open(argv[2],O_WRONLY|O_CREAT);
	
		char *c = (char *) calloc(1, sizeof(char)); 
	
	
		while(read(f1,c,1))	
		{
			write(f2,c,1);
		}

		close(f1);
		close(f2);

		printf("Contents copied.\n\n");
		return 0;
	}

	char option=argv[1][1];
	int f1 = open(argv[2],O_RDONLY);
	if(f1 == -1)
	{
		printf("File doesn't exist\n\n");
		return 0;
	}

	if(option=='i')
	{
		int f2 = open(argv[3],O_RDONLY);
		char *c = (char *) calloc(1, sizeof(char)); 
		if(f2==-1)
		{
			f2 = creat(argv[3],0666);
			while(read(f1,c,1))	
			{
				write(f2,c,1);
			}
			printf("Contents copied.\n\n");
		}
		else
		{
			close(f2);
			f2 = open(argv[3],O_WRONLY);
			printf("Want to overwrite %s?(y/n): ",argv[3]);
			char ch;
			scanf("%c",&ch);
			if(ch=='y')
			{
				while(read(f1,c,1))	
				{
					write(f2,c,1);
				}
			printf("Contents copied.\n\n");			
			}
		}
		
		close(f2);
	}

	else if(option=='f')
	{
		int f2 = open(argv[3],O_RDONLY);
		char *c = (char *) calloc(1, sizeof(char)); 
		if(f2==-1)
		{
			f2 = creat(argv[3],0666);
			while(read(f1,c,1))	
			{
				write(f2,c,1);
			}
			printf("Contents copied.\n\n");
		}

		else
		{
			close(f2);
			f2 = open(argv[3],O_WRONLY);
			printf("\nOverwriting....");
			while(read(f1,c,1))	
			{
				write(f2,c,1);
			}
			printf("Contents copied.\n\n");	
		}
		close(f2);

	}

	else if(option=='n')
	{
		int f2 = open(argv[3],O_RDONLY);
		char *c = (char *) calloc(1, sizeof(char)); 
		if(f2==-1)
		{
			f2 = creat(argv[3],0666);
			while(read(f1,c,1))	
			{
				write(f2,c,1);
			}
			printf("Contents copied.\n\n");
		}

		else
		{
			printf("\nCannot overwrite (noclobber)\n");
		}
		close(f2);

	}
	
	close(f1);
	return 0;
	
}
