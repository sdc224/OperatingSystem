/*
 * This program is based on a scheduling algorithm Shortest Job First Non preemptive
 * Here, the main logic is, we just have to execute those processes that have
 * lower burst time as compared to others, we also have a look at arrival time.
 */

#include<stdio.h>

typedef struct operation
{
	int process;
	int arrival_time;
	int burst_time;

}operation;

int burst_time = 0;

void swap(operation *a, operation *b)
{
	const operation temp = *a;
	*a = *b;
	*b = temp;
}

int compare_arrival_time(operation q[], const int a, const int b)
{
	return q[a].arrival_time < q[b].arrival_time;
}

int main()
{
	int i, n, k = 1;
	int j, weight_time[10], turn_around_time[10], turn_around=0, sum=0;

	operation process[10];

	float turn_sum = 0, wait_sum = 0;

	printf("\nEnter the No. of processes :");
	scanf_s("%d", &n);
	 
	for (i = 0; i < n; i++)
	{
		process[i].process = i + 1;
		printf("\tEnter the burst time of %d process :", i+1);
		scanf_s(" %d", &process[i].burst_time);
		printf("\tEnter the arrival time of %d process :", i+1);
		scanf_s(" %d", &process[i].arrival_time);
	}
	 
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (compare_arrival_time(process, i, j))
				swap(&process[i], &process[j]);

	for (j = 0; j < n; j++)
	{
		burst_time = burst_time + process[j].burst_time;
		const int min = process[k].burst_time;

		for (i = k; i < n; i++)
			if (burst_time >= process[i].arrival_time && process[i].burst_time < min)
				swap(&process[i], &process[k]);

		k++;
	}
	
	weight_time[0]=0;
	
	for (i = 1; i < n; i++)
	{
		sum = sum + process[i - 1].burst_time;
		weight_time[i] = sum - process[i].arrival_time;
		wait_sum = wait_sum + weight_time[i];
	}

	const float wait_avg = wait_sum / n;
	for (i = 0; i < n; i++)
	{
		turn_around = turn_around + process[i].burst_time;
		turn_around_time[i] = turn_around - process[i].arrival_time;
		turn_sum = turn_sum + turn_around_time[i];
	}

	const float turn_avg = turn_sum / n;
	 
	printf("\n************************");

	printf("\nProcess\t Arrival\t Burst\t Waiting\t Turn-around");
	for(i = 0; i < n; i++)
	{
		printf("\n   p%d\t %3d\t\t %3d\t %5d\t\t%7d",process[i].process,process[i].arrival_time,process[i].burst_time,weight_time[i],turn_around_time[i]);
	}
	 
	printf("\n\nAverage Wait Time : %f", wait_avg);
	printf("\n\nAverage Turn Around Time : %f\n", turn_avg);
	return 0;
}