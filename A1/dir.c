#include <sys/types.h>
#include <dirent.h>
#include<stdlib.h>
#include<stdio.h>

void main()
{
	int sz,fd;
	char *c = (char *) calloc(100, sizeof(char));
	fd = opendir("folder");
	if( fd != NULL)
	{
		printf("Directory opened\n");
		sz = readdir(fd, c, 100); 
		c[sz] = '\0'; 
		printf("The contents are : %s\n", c); 
	}
	else
		printf("Directory is not opened\n");

}

