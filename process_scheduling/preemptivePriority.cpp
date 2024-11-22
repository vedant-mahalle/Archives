#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id; 
    int at; 
    int bt; 
    int pt; 
    int ct; 
    int tat; 
    int wt; 
};

bool comparison(const Process &p1, const Process &p2) {
    return p1.at < p2.at;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Process ID starts from 1
        cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt >> processes[i].pt;
    }

    sort(processes.begin(), processes.end(), comparison);

    int currentTime = 0;
    int completed = 0;
    vector<bool> isCompleted(n, false);
    int currentProcess = -1;

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && !isCompleted[i] && processes[i].pt < highestPriority) {
                highestPriority = processes[i].pt; 
                idx = i; 
            }
        }

        if (idx != -1) {
            if (currentProcess == -1) {
                currentProcess = idx;
            }

            processes[currentProcess].bt--;
            currentTime++;

            if (processes[currentProcess].bt == 0) {
                processes[currentProcess].ct = currentTime; 
                processes[currentProcess].tat = processes[currentProcess].ct - processes[currentProcess].at;
                processes[currentProcess].wt = processes[currentProcess].tat - processes[currentProcess].bt; 
                isCompleted[currentProcess] = true; 
                completed++; 
                currentProcess = -1; 
            }

            if (idx != currentProcess) {
                currentProcess = idx; 
            }
        } else {
            currentTime++; 
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" 
             << processes[i].at << "\t\t" 
             << processes[i].bt << "\t\t" 
             << processes[i].pt << "\t\t" 
             << processes[i].ct << "\t\t" 
             << processes[i].tat << "\t\t" 
             << processes[i].wt << endl;
    }

    return 0;
}
