#include<iostream>
#include<vector>
#include<deque>
#include<cmath>
using namespace std;

struct Process {
    int arrival;
    int burst;
    int index;
};

void roundRo(int n, Process p[], int wait[], int tat[], int quan) {
    vector<int> remainBurst(n);
    deque<int> q;
    int time = 0, complete = 0;
    vector<bool> inQueue(n, false); 

    for (int i = 0; i < n; i++) {
        remainBurst[i] = p[i].burst;
    }


    for (int i = 0; i < n; i++) {
        if (p[i].arrival <= time && remainBurst[i] > 0) {
            q.push_back(i);
            inQueue[i] = true;
        }
    }

    while (complete < n) {
        if (!q.empty()) {
            int indx = q.front(); 
            q.pop_front();       

           
            int execTime = min(quan, remainBurst[indx]);
            remainBurst[indx] -= execTime;
            time += execTime;

           
            if (remainBurst[indx] == 0) {
                tat[indx] = time - p[indx].arrival;   
                wait[indx] = tat[indx] - p[indx].burst;  
                complete++;
                inQueue[indx] = false;
            }

            
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && p[i].arrival <= time && remainBurst[i] > 0) {
                    q.push_back(i);
                    inQueue[i] = true;
                }
            }

          
            if (remainBurst[indx] > 0) {
                q.push_back(indx);
            }
        } else {
            time++;
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
    int n, quantum;
    cout << "\nEnter the Total count of Process & Quantum No: ";
    cin >> n >> quantum;

    Process p[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter the arrival and burst time of " << i + 1 << " Process: ";
        cin >> p[i].arrival >> p[i].burst;
        p[i].index = i;
    }

    int wait[n] = {0}, tat[n] = {0};

    roundRo(n, p, wait, tat, quantum);

    cout << "\nProcess\tArrival\tBurst\tWait\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].index + 1 << "\t" << p[i].arrival << "\t" << p[i].burst
             << "\t" << wait[i] << "\t" << tat[i] << endl;
    }

    cout << "\nAverage TAT = " << average(n, tat);
    cout << "\nAverage WT = " << average(n, wait);

    return 0;
}
