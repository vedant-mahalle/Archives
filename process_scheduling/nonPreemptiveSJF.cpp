#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id; 
    int at; 
    int bt; 
    int tat; 
    int wt; 
};

bool comparison(const Process &p1, const Process &p2) {
    return p1.bt < p2.bt; 
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Process ID starts from 1
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &p1, const Process &p2) {
        return p1.at < p2.at;
    });

    int currentTime = 0;
    vector<bool> finished(n, false);

    for (int i = 0; i < n; i++) {
        int idx = -1;
        int min_bt = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!finished[j] && processes[j].at <= currentTime) {
                if (processes[j].bt < min_bt) {
                    min_bt = processes[j].bt;
                    idx = j;
                }
            }
        }

        if (idx != -1) { 
            currentTime += processes[idx].bt; 
            processes[idx].tat = currentTime - processes[idx].at; 
            processes[idx].wt = processes[idx].tat - processes[idx].bt; 
            finished[idx] = true; 
        } else {
            currentTime++;
            i--; 
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" 
             << processes[i].at << "\t\t" 
             << processes[i].bt << "\t\t" 
             << processes[i].wt << "\t\t" 
             << processes[i].tat << endl;
    }

    return 0;
}
