#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>

/*void ls_rec(char *name)
{	
	char path[1000];
	struct dirent *de;
	DIR *dir=opendir(name);
	
	if(dir==NULL)
		return;
	while((de=readdir(dir))!=NULL)
	{
		if(strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0)
		{
			printf("%s\n",de->d_name);
			strcpy(path,name);
			strcat(path,"/");
			strcat(path,de->d_name);
			ls_rec(path);
			
		}
	}
	closedir(dir);
}
*/
int main(int argc, char *argv[])
{

	struct dirent *de;

	if(argc==2)
	{
		DIR *dir=opendir(argv[1]);
		
		if(dir==NULL)
		{
			printf("Unable to open directory");
			return 0;
		}			
		while((de = readdir(dir)))
			if (de->d_name[0]!='.')
				printf("%s ",de->d_name);
		printf("\n");
		closedir(dir);
		return 0;
	}

	else if(argc==3)
	{		

		DIR *dir=opendir(argv[2]);
		
		if(dir==NULL)
		{
			printf("Unable to open directory");
			return 0;
		}	

		de=readdir(dir);

		if(argv[1][1]=='1')
		{
			while(de)
			{
				if (de->d_name[0]!='.')
					printf("%s\n",de->d_name);
				de=readdir(dir);
			}
		}
		
		else if(argv[1][1]=='a')
		{
			while(de)
			{
				printf("%ld  %s\n",de->d_ino,de->d_name);
				de=readdir(dir);
			}
		}

		else if(argv[1][1]=='r')
		{

			char arr[100][100];
			int c = -1;
			
			while(de)
			{
				if(de->d_name[0] != '.')
					strcpy(arr[++c],de->d_name);
				de=readdir(dir);
			}
			
			for(;c > -1;c--)
				printf("%s\n",arr[c]);			
		}			

		else
			printf("Invalid argument\n");

		/*else if(argv[1][1]=='r')
		{
			char arr[50][50];
			int count=0;
			DIR *dir=opendir(argv[2]);
		
			if(dir==NULL)
			{
				printf("Unable to open directory");
				return 0;
			}			
			while((de = readdir(dir)))
			{
				printf("%s\n",de->d_name);
				//strcpy(arr[count],de->d_name);
				//count++;
			}		
			for(int i=count-1;i>=0;i++)
			{
				printf("%s\n",arr[i]);
			}
	
			closedir(dir);
					
		}*/

		closedir(dir);
		return 0;
	}

	else
		printf("Invalid no. of arguments\n");
}
