#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Process {
    int arrival;
    int burst;
    int index;
};

void sjfPreemptive(int n, Process p[], int wait[], int tat[]) 
{
    	vector<int> remainBurst(n);
    	int time = 0, complete = 0;
    	vector<bool> isCompleted(n, false);

    	for (int i = 0; i < n; i++) 
	{
        	remainBurst[i] = p[i].burst;
    	}
    	while (complete < n) 
	{
        	int shortestIndex = -1;
        	int minBurst = 999999;

       		for (int i = 0; i < n; i++) 
		{
            		if (p[i].arrival <= time && !isCompleted[i] && remainBurst[i] < minBurst && remainBurst[i] > 0) 
			{
                		minBurst = remainBurst[i];
                		shortestIndex = i;
            		}
        	}

        	if (shortestIndex == -1) 
		{
            		time++;
            		continue;
        	}

        	remainBurst[shortestIndex] -= 1;
        	time += 1;

        	if (remainBurst[shortestIndex] == 0) 
		{
            		tat[shortestIndex] = time - p[shortestIndex].arrival;
            		wait[shortestIndex] = tat[shortestIndex] - p[shortestIndex].burst;
            		complete++;
            		isCompleted[shortestIndex] = true;
        	}
    
	}
}

float average(int n, int arr[]) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (float) sum / n;
}

int main() {
    int n;
    cout << "\nEnter the Total count of Process: ";
    cin >> n;

    Process p[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter the arrival and burst time of " << i + 1 << " Process: ";
        cin >> p[i].arrival >> p[i].burst;
        p[i].index = i;
    }

    int wait[n] = {0}, tat[n] = {0};

    sjfPreemptive(n, p, wait, tat);

    cout << "\nProcess\tArrival\tBurst\tWait\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].index + 1 << "\t" << p[i].arrival << "\t" << p[i].burst
             << "\t" << wait[i] << "\t" << tat[i] << endl;
    }

    cout << "\nAverage TAT = " << average(n, tat);
    cout << "\nAverage WT = " << average(n, wait);

    return 0;
}
