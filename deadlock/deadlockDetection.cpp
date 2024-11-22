#include <bits/stdc++.h>
using namespace std;

bool check(vector<int>& v1, vector<int>& v2) {
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] > v2[i]) {
            return false;
        }
    }
    return true;
}

bool allFinish(vector<bool>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (!v[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, r;
    cout << "Enter the number of processes and the number of resources" << endl;
    cin >> n >> r;

    bool deadlock = true;
    vector<vector<int>> allocation(n, vector<int>(r));  
    vector<vector<int>> request(n, vector<int>(r));   
    vector<int> sequence;                              
    vector<bool> finish(n, false);                    

    vector<int> work(r);  

    for (int i = 0; i < n; i++) {
        cout << "Enter the allocation for process " << i + 1 << endl;
        for (int j = 0; j < r; j++) {
            cin >> allocation[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter request for process " << i + 1 << endl;
        for (int j = 0; j < r; j++) {
            cin >> request[i][j];
        }
    }

    cout << "Enter the available resources" << endl;
    for (int i = 0; i < r; i++) {
        cin >> work[i];
    }

    while (true) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i] && check(request[i], work)) {
                found = true;

                for (int j = 0; j < r; j++) {
                    work[j] += allocation[i][j];
                }

                finish[i] = true; 
                sequence.push_back(i);
            }
        }

        if (!found) {
            break;
        }

        if (allFinish(finish)) {
            deadlock = false;
            break;
        }
    }

    if (!deadlock) {
        cout << "There is no deadlock in the system" << endl;
        cout << "Safe sequence: ";
        for (int i = 0; i < sequence.size(); i++) {
            cout << "P" << sequence[i] + 1 << " ";
        }
        cout << endl;
    } else {
        cout << "Deadlock exists in the system" << endl;
    }

    return 0;
}
