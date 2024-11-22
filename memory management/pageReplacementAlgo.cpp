#include <bits/stdc++.h>
using namespace std;

void printMemory(vector<int>& memory, string action) {
    cout << "Memory: [ ";
    for (int m : memory) cout << (m == -1 ? "_" : to_string(m)) << " ";
    cout << "] Action: " << action << endl;
}

int lru(vector<int> seq) {
    int faults = 0;
    vector<int> memory(3, -1);
    int n = seq.size();

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < 3; j++) {
            if (seq[i] == memory[j]) {
                found = true;
                for (int k = j; k < 2; k++) {
                    memory[k] = memory[k + 1];
                }
                memory[2] = seq[i];
                printMemory(memory, "Hit: " + to_string(seq[i]));
                break;
            }
        }
        if (!found) {
            faults++;
            for (int j = 0; j < 2; j++) {
                memory[j] = memory[j + 1];
            }
            memory[2] = seq[i];
            printMemory(memory, "Fault: " + to_string(seq[i]));
        }
    }
    return faults;
}

int nextAccess(vector<int> seq, int idx, int x) {
    for (int i = idx + 1; i < seq.size(); i++) {
        if (seq[i] == x) return i;
    }
    return INT_MAX;
}

int optimal(vector<int> seq, int x) {
    int faults = 0;
    vector<int> memory(3, -1);

    for (int i = 0; i < seq.size(); i++) {
        bool found = false;
        for (int j = 0; j < 3; j++) {
            if (seq[i] == memory[j]) {
                found = true;
                printMemory(memory, "Hit: " + to_string(seq[i]));
                break;
            }
        }
        if (found) continue;
        faults++;

        int farthest = -1, index_to_replace = -1;
        for (int j = 0; j < 3; j++) {
            if (memory[j] == -1) {
                index_to_replace = j;
                break;
            }
            int next_idx = nextAccess(seq, i, memory[j]);
            if (next_idx > farthest) {
                farthest = next_idx;
                index_to_replace = j;
            }
        }
        memory[index_to_replace] = seq[i];
        printMemory(memory, "Fault: " + to_string(seq[i]));
    }
    return faults;
}

int fifo(vector<int> seq, int x) {
    queue<int> q;
    int faults = 0;
    vector<int> map(x, 0);
    vector<int> memory(3, -1);

    for (int i = 0; i < seq.size(); i++) {
        if (map[seq[i]] != 0) {
            printMemory(memory, "Hit: " + to_string(seq[i]));
            continue;
        }
        faults++;
        if (q.size() == 3) {
            int front = q.front();
            map[front]--;
            q.pop();
            auto it = find(memory.begin(), memory.end(), front);
            if (it != memory.end()) *it = seq[i];
        } else {
            memory[q.size()] = seq[i];
        }
        q.push(seq[i]);
        map[seq[i]]++;
        printMemory(memory, "Fault: " + to_string(seq[i]));
    }
    return faults;
}

int main() {
    int n, x;
    cout << "Enter the number of elements in reference string sequence and unique processes" << endl;
    cin >> n >> x;
    vector<int> sequence(n);
    for (int i = 0; i < n; i++) cin >> sequence[i];

    cout << "Page faults in FIFO: " << fifo(sequence, x) << endl;
    cout << "Page faults in LRU: " << lru(sequence) << endl;
    cout << "Page faults in Optimal: " << optimal(sequence, x) << endl;

    return 0;
}
