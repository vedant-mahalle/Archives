#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int burstTime;  
    int arrivalTime;
    int priority;
};



void nonPreemptivePriorityScheduling(vector<Process> &processes) {
    int n = processes.size();
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> completionTime(n, 0);

    
    completionTime[0] = processes[0].arrivalTime + processes[0].burstTime;
    for (int i = 1; i < n; i++) {
        if (processes[i].arrivalTime > completionTime[i - 1]) {
            completionTime[i] = processes[i].arrivalTime + processes[i].burstTime;
        } else {
            completionTime[i] = completionTime[i - 1] + processes[i].burstTime;
        }
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i] - processes[i].arrivalTime;
        waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
    }

    cout << setw(10) << "Process ID" << setw(15) << "Arrival Time" << setw(10) << "Burst Time"
         << setw(10) << "Priority" << setw(15) << "Completion Time" << setw(15) << "Turnaround Time"
         << setw(10) << "Waiting Time" << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(10) << processes[i].id << setw(15) << processes[i].arrivalTime << setw(10)
             << processes[i].burstTime << setw(10) << processes[i].priority << setw(15)
             << completionTime[i] << setw(15) << turnaroundTime[i] << setw(10) << waitingTime[i] << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        processes[i].id = i + 1; 
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
    }

    nonPreemptivePriorityScheduling(processes);
    
    return 0;
}
