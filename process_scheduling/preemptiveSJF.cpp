#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, at, bt, bt_remaining, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
        processes[i].bt_remaining = processes[i].bt;
    }

    int currentTime = 0, completed = 0, minIndex;
    bool isProcessSelected = false;

    while (completed < n) {
        minIndex = -1;
        int minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && processes[i].bt_remaining > 0 && processes[i].bt_remaining < minBurst) {
                minBurst = processes[i].bt_remaining;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            currentTime++;
        } else {
            processes[minIndex].bt_remaining--;
            currentTime++;

            if (processes[minIndex].bt_remaining == 0) {
                processes[minIndex].ct = currentTime;
                processes[minIndex].tat = processes[minIndex].ct - processes[minIndex].at;
                processes[minIndex].wt = processes[minIndex].tat - processes[minIndex].bt;
                completed++;
            }
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" 
             << processes[i].at << "\t\t" 
             << processes[i].bt << "\t\t" 
             << processes[i].ct << "\t\t" 
             << processes[i].tat << "\t\t" 
             << processes[i].wt << endl;
    }

    return 0;
}
