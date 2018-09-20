/*
 * This program is based on a scheduling algorithm First Come First Serve
 * Here, the main logic is, we just have to execute those processes that are
 * coming first based on their arrival time, without watching the burst time.
 */

#include <stdio.h>

typedef struct operations
{
	int id;
	int arrival_time;
	int burst_time;
}operation;

void swap(operation *a, operation *b)
{
	const operation temp = *a;
	*a = *b;
	*b = temp;
}

int main(void)
{
	operation op[] = { { 1, 5, 1 }, { 2, 7, 5}, { 3, 2, 11 }, { 4, 0, 8 }, { 5, 3, 7 } };
	const int n = sizeof op / sizeof op[0];

	// Sorting based on arrival time
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (op[j].arrival_time > op[j + 1].arrival_time)
				swap(&op[j], &op[j + 1]);
		}
	}

	printf("Operations are: \n");
	printf("\tId\tArrival Time\tBurst Time\n");
	for (int i = 0; i < n; i++)
	{
		printf("%10d%10d%20d\n", op[i].id, op[i].arrival_time, op[i].burst_time);
	}
	printf("\n");
	
	return 0;
}