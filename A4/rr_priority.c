#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int pid;
	int start;
	int arr;
	int burst;
	int pri;
	int rem;
	int wait;
	int turn;
	int flag;
}job;

void gantt(job arr[], int n, int tot_time)
{
	if(n <= 0)
	return;
	
	printf("\n\n\tGANTT CHART");
	
	int i, j;
	
	// printing the top bar
	printf("\n\n\t ");
	for(i=0; i<n-1; i++)
	{
	for(j=arr[i].start; j<arr[i+1].start; j++)
	printf("--");
	printf(" ");
	}
	
	for(j=0; j<tot_time - arr[n-1].start; j++)
	printf("--");
	printf(" ");
	
	printf("\n\t|");
	
	// printing the process id in the middle
	for(i=0; i<n-1; i++)
	{
	for(j=arr[i].start; j<arr[i+1].start - 1; j++)
	printf(" ");
	printf("P%d", arr[i].pid);
	
	for(j=arr[i].start; j<arr[i+1].start - 1; j++)
	printf(" ");
	printf("|");
	}
	
	for(j=0; j<tot_time - arr[n-1].start - 1; j++)
	printf(" ");
	printf("P%d", arr[n-1].pid);
	for(j=0; j<tot_time - arr[n-1].start - 1; j++)
	printf(" ");
	printf("|");
	
	printf("\n\t ");
	
	// printing the bottom bar
	for(i=0; i<n-1; i++)
	{
	for(j=arr[i].start; j<arr[i+1].start; j++)
	printf("--");
	printf(" ");
	}
	
	for(j=0; j<tot_time - arr[n-1].start; j++)
	printf("--");
	printf(" ");
	
	printf("\n\t");
	
	// printing the time line
	for(i=0; i<n-1; i++)
	{
	printf("%d", arr[i].start);
	for(j=arr[i].start; j<arr[i+1].start; j++)
		printf("  ");
	if(arr[i].start > 9)
		printf("\b");
	
	}
	
	printf("%d", arr[n-1].start);
	for(j=0; j<tot_time - arr[n-1].start; j++)
		printf("  ");
	if(tot_time > 9)
		printf("\b%d", tot_time);
	printf("\n");
}

void display(job ar[],int n)
{
	float avgturn=0,avgwait=0;
	job temp;
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(ar[j].pid<ar[i].pid)
			{
				temp=ar[j];
				ar[j]=ar[i];
				ar[i]=temp;
			}
		
		}
	}
	printf("-------------------------------------------------------------------------------");
	printf("\nProcess ID\tArrival Time\tBurst Time\tTurnaround\tWaiting Time\n");
	printf("-------------------------------------------------------------------------------");
	for(int i=0;i<n;i++)
	{
		printf("\nP%d\t\t%d\t\t%d\t\t%d\t\t%d",ar[i].pid,ar[i].arr,ar[i].burst,ar[i].turn,ar[i].wait);
		avgturn+=ar[i].turn;
		avgwait+=ar[i].wait;
	}
	printf("\n\t\t\t\t\t\t------\t\t------\n");
	printf("\t\t\t\tAverage:\t%.2f\t\t%.2f\n",avgturn/n,avgwait/n);
	printf("\t\t\t\t\t\t------\t\t------\n");
}

void rr(job ar[],int n)
{
	int time=0;
	float avgturn=0,avgwait=0;
	int prev=-1;
	printf("\n\n\t\tROUND ROBIN\n\n");
	time=0;
	int remain=0,endtime;
	int q;
	q=2;
	int t=0;
	int i=0;
	job temp;
	job g[10];
	int count=0;
	
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(ar[j].arr<ar[i].arr)
			{
				temp=ar[j];
				ar[j]=ar[i];
				ar[i]=temp;
			}
		}
	}
	
	for(int i=0;i<n;i++)
	{
		time+=ar[i].burst;
	}
	
	while(remain!=n)
	{
		if(ar[i].flag==0)
		{
		
			if(ar[i].rem>q && ar[i].flag==0)
			{
				ar[i].start=t;
				g[count++]=ar[i];
				t=t+q;
				ar[i].rem-=q;
			}
			else if(ar[i].flag==0)
			{
				ar[i].start=t;
				g[count++]=ar[i];
				t=t+ar[i].rem;
				ar[i].rem=0;
			}
			if(ar[i].rem==0)
			{
				remain++;
				endtime=t;
				ar[i].turn=endtime-ar[i].arr;
				ar[i].wait=endtime-ar[i].burst-ar[i].arr;
				ar[i].flag=1;
			}
			i=(i+1)%n;
		}
		else
		{
			i=(i+1)%n;
		}
	}
	display(ar,n);
	gantt(g,count,time);
}

void priority_np(job ar[],int n)
{
	int time=0;
	float avgturn=0,avgwait=0;
	int min;
	int index;
	job g[10];
	int count=0;
	
	printf("\n\n\t\tPRIORITY (Non Preemptive)\n\n");
	time=0;
	for(int i=0;i<n;i++)
	{
		time+=ar[i].burst;
	}

	for(int t=0;t<time;)
	{
		min=9999;
		for(int i=0;i<n;i++)
		{
			if(ar[i].arr<=t && ar[i].pri<min && ar[i].flag==0)
			{
				min=ar[i].pri;
				index=i;
			}
		}
		ar[index].flag=1;
		ar[index].wait=t-ar[index].arr;
		ar[index].start=t;
		g[count++]=ar[index];
		t+=ar[index].burst;
		ar[index].turn=t-ar[index].arr;
	}
	display(ar,n);
	gantt(g,count,time);
}

void priority_p(job ar[],int n)
{
	int time=0;
	float avgturn=0,avgwait=0;
	int min;
	int index;
	int prev=-1;
	printf("\n\n\t\tPRIORITY (Preemptive)\n\n");
	time=0;
	int remain=0,endtime;
	job g[10];
	int count=0;
	
	for(int i=0;i<n;i++)
	{
		time+=ar[i].burst;
	}
	
	for(int t=0;remain!=n;t++)
	{
		min=9999;
		for(int i=0;i<n;i++)
		{
			if( ar[i].arr<=t && ar[i].pri<min && ar[i].rem>0)
			{
				min=ar[i].pri;
				index=i;
			}
		}
		if(count!=0 && g[count-1].pid != ar[index].pid)
		{
			ar[index].start=t;
			g[count++]=ar[index];
		}
		else if(count==0 && t==0)
		{
			ar[index].start=t;
			g[count++]=ar[index];
		}
		ar[index].rem-=1;
		
		if(ar[index].rem==0)
		{
			remain++;
			endtime=t+1;
			ar[index].turn=endtime-ar[index].arr;
			ar[index].wait=endtime-ar[index].burst-ar[index].arr;
		}	
	}
	display(ar,n);
	gantt(g,count,time);
}

void input(job ar[],int n)
{
	for(int i=0;i<n;i++)
	{
		printf("\n\t\tEnter PID : ");
		scanf("%d",&ar[i].pid);
		printf("\t\tEnter Arrival Time : ");
		scanf("%d",&ar[i].arr);
		printf("\t\tEnter Burst Time : ");
		scanf("%d",&ar[i].burst);
		printf("\t\tEnter Priority : ");
		scanf("%d",&ar[i].pri);
		ar[i].rem=ar[i].burst;
		ar[i].flag=0;
	}
	printf("\n");
}

int main()
{
	job ar[10];
	int n;
	char ch;
	int time=0;
	float avgturn=0,avgwait=0;
	int min;
	int index;
	int choice,op;
	do
	{
		printf("\n\n\t\tCPU SCHEDULING ALGORITHMS\n");
		printf("\n1.ROUND ROBIN\n2.PRIORITY\n3.EXIT\nEnter Choice : ");
		scanf("%d",&choice);
		if(choice==1)
		{		
				printf("\n\t\tROUND ROBIN CPU SCHEDULER\n");
				printf("\t\tEnter Number of Processes : ");
				scanf("%d",&n);
				input(ar,n);
				rr(ar,n);
		}
	
		else if(choice == 2)
		{
				printf("\n\t\tPRIORITY CPU SCHEDULER\n");
				printf("\t\t1. Non Preemptive PRIORITY\n\t\t2. Preemptive PRIORITY\n\t\tEnter your option : ");
				scanf("%d",&op);
				printf("\t\tEnter Number of Processes : ");
				scanf("%d",&n);
				input(ar,n);
				if(op==1)
					priority_np(ar,n);
				else if(op==2)
					priority_p(ar,n);
				else
					printf("\t\tInvalid Choice !!!\n");
		}
		
		else
			exit(0);

	printf("Want to continue?(y/n): ");
	scanf(" %c",&ch);
	}while(ch=='y');
	return 0;
}
