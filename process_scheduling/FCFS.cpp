#include <bits/stdc++.h>
using namespace std;

struct Process {
    int at;
    int bt; 
    int tat; 
    int wt; 
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
    }

    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].at) {
            currentTime = processes[i].at;
        }

        processes[i].wt = currentTime - processes[i].at; 
        currentTime += processes[i].bt;
        processes[i].tat = processes[i].wt + processes[i].bt; 
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << (i + 1) << "\t" 
             << processes[i].at << "\t\t" 
             << processes[i].bt << "\t\t" 
             << processes[i].wt << "\t\t" 
             << processes[i].tat << endl;
    }

    return 0;
}
