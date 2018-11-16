// C program to implement Round Robin Scheduling

#include <stdio.h>

typedef struct operation
{
	int process;
	int arrival_time;
	int burst_time;

}operation;

void find_waiting_time(const int n, const int burst_time[], int weight_time[], const int quantum) 
{ 
	int rem_bt[10];
	for (int i = 0 ; i < n ; i++) 
		rem_bt[i] =  burst_time[i];
  
	int t = 0;
  
	while (1)
	{
		int done = 1; 
  
		for (int i = 0 ; i < n; i++) 
		{ 
			if (rem_bt[i] > 0) 
			{ 
				done = 0;
  
				if (rem_bt[i] > quantum) 
				{ 
					t += quantum;  
					rem_bt[i] -= quantum; 
				}
				
				else
				{ 
					t = t + rem_bt[i];  
					weight_time[i] = t - burst_time[i];  
					rem_bt[i] = 0;
				}
			}
		}

		if (done == 1) 
		  break;
	}
}
  
void find_turn_around_time(const int n, const int burst_time[], const int weight_time[], int turn_around_time[])
{ 
	for (int i = 0; i < n ; i++) 
		turn_around_time[i] = burst_time[i] + weight_time[i]; 
} 
  
void find_average_time(int processes[], const int n, int bt[], const int quantum) 
{ 
	int wt[10], tat[10], total_wt = 0, total_tat = 0; 
  
	find_waiting_time(n, bt, wt, quantum); 
  
	find_turn_around_time(n, bt, wt, tat);

	printf("\n*********************************\n");
	printf("Processes  Burst time  Waiting time  Turn around time\n"); 
  
	for (int i=0; i<n; i++) 
	{ 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
		printf("  p%d\t\t%d\t%d\t\t%d\n", i+1, bt[i], wt[i], tat[i]); 
	} 
  
	printf("\nAverage waiting time = %f\n", (float)total_wt / (float)n); 
	printf("\nAverage waiting time = %f\n", (float)total_tat / (float)n); 
} 
  
// Driver code 
int main() 
{ 
	int processes[] = { 1, 2, 3};
	const int n = sizeof processes / sizeof processes[0]; 
  
	int burst_time[] = {10, 5, 8}; 
  
	const int quantum = 2; 
	find_average_time(processes, n, burst_time, quantum); 
	return 0; 
} 