// C program to implement Shortest Job Next ( Preemptive)

#include <stdio.h>
#include <limits.h>

typedef struct operation 
{ 
	int process;
	int burst_time;
	int arrival_time;

}operation;

void find_waiting_time(operation process[], const int n, int wait_time[]) 
{ 
	int burst_time[10]; 
  
	for (int i = 0; i < n; i++) 
		burst_time[i] = process[i].burst_time;

	int complete = 0;
	int t = 0;
	int min = INT_MAX;
	int shortest = 0; 
	int check = 0; 
  
	while (complete != n) 
	{
  
		for (int j = 0; j < n; j++) 
		{ 
			if (process[j].arrival_time <= t && burst_time[j] < min && burst_time[j] > 0) 
			{ 
				min = burst_time[j]; 
				shortest = j; 
				check = 1; 
			}
		}
  
		if (check == 0) 
		{ 
			t++;
			continue; 
		} 
  
		burst_time[shortest]--; 
  
		min = burst_time[shortest];

		if (min == 0) 
			min = INT_MAX;

		if (burst_time[shortest] == 0) 
		{
			complete++;
			check = 0;

			const int finish_time = t + 1;

			wait_time[shortest] = finish_time - process[shortest].burst_time - process[shortest].arrival_time;

			if (wait_time[shortest] < 0)
				wait_time[shortest] = 0;
		}
		
		t++;
	}
}

void find_turn_around_time(operation process[], const int n, const int wait_time[], int turn_around_time[]) 
{ 
	for (int i = 0; i < n; i++) 
		turn_around_time[i] = process[i].burst_time + wait_time[i]; 
} 
  
void find_average_time(operation process[], const int n) 
{ 
	int weight_time[10], turn_around_time[10], total_weight = 0, total_turn_around_time = 0; 

	find_waiting_time(process, n, weight_time); 

	find_turn_around_time(process, n, weight_time, turn_around_time);

	printf("\nProcess   Arrival Time   Burst Time   Wait Time   Turn Around Time\n");
  
	for (int i = 0; i < n; i++) 
	{ 
		total_weight = total_weight + weight_time[i]; 
		total_turn_around_time = total_turn_around_time + turn_around_time[i]; 
		printf("  p%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process[i].process, process[i].arrival_time, process[i].burst_time, weight_time[i], turn_around_time[i]); 
	}

	const float average_wait_time = (float)total_weight / n;
	const float average_turn_around_time = (float)total_turn_around_time / n;

	printf("\nAverage Wait Time = %f\nAverage Turn Around Time = %f\n", average_wait_time, average_turn_around_time);
}

int main(void)
{ 
	operation process[] = { { 1, 6, 1 }, { 2, 8, 1 }, { 3, 7, 2 }, { 4, 3, 3 } };
	const int n = sizeof process / sizeof process[0]; 
  
	find_average_time(process, n); 
	return 0; 
} 