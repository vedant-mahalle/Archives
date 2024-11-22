#include <iostream>
#include <climits>
using namespace std;

void printMemory(int blocks[], int m) {
    cout << "Memory State: [";
    for (int i = 0; i < m; ++i) {
        cout << blocks[i] << (i < m - 1 ? ", " : "");
    }
    cout << "]\n";
}

void firstFit(int blocks[], int m, int requests[], int n) {
    cout << "\nFirst Fit Allocation:\n";
    for (int i = 0; i < n; ++i) {
        bool allocated = false;
        for (int j = 0; j < m; ++j) {
            if (blocks[j] >= requests[i]) {
                cout << "Request " << requests[i] << " allocated to block " << j << "\n";
                blocks[j] -= requests[i];
                allocated = true;
                break;
            }
        }
        if (!allocated) cout << "Request " << requests[i] << " could not be allocated.\n";
        printMemory(blocks, m);
    }
}

void nextFit(int blocks[], int m, int requests[], int n) {
    cout << "\nNext Fit Allocation:\n";
    int lastIndex = 0;
    for (int i = 0; i < n; ++i) {
        bool allocated = false;
        int j = lastIndex;
        do {
            if (blocks[j] >= requests[i]) {
                cout << "Request " << requests[i] << " allocated to block " << j << "\n";
                blocks[j] -= requests[i];
                lastIndex = j;
                allocated = true;
                break;
            }
            j = (j + 1) % m;
        } while (j != lastIndex);
        if (!allocated) cout << "Request " << requests[i] << " could not be allocated.\n";
        printMemory(blocks, m);
    }
}

void bestFit(int blocks[], int m, int requests[], int n) {
    cout << "\nBest Fit Allocation:\n";
    for (int i = 0; i < n; ++i) {
        int bestIndex = -1;
        int minSize = INT_MAX;
        for (int j = 0; j < m; ++j) {
            if (blocks[j] >= requests[i] && blocks[j] < minSize) {
                minSize = blocks[j];
                bestIndex = j;
            }
        }
        if (bestIndex != -1) {
            cout << "Request " << requests[i] << " allocated to block " << bestIndex << "\n";
            blocks[bestIndex] -= requests[i];
        } else {
            cout << "Request " << requests[i] << " could not be allocated.\n";
        }
        printMemory(blocks, m);
    }
}

void worstFit(int blocks[], int m, int requests[], int n) {
    cout << "\nWorst Fit Allocation:\n";
    for (int i = 0; i < n; ++i) {
        int worstIndex = -1;
        int maxSize = -1;
        for (int j = 0; j < m; ++j) {
            if (blocks[j] >= requests[i] && blocks[j] > maxSize) {
                maxSize = blocks[j];
                worstIndex = j;
            }
        }
        if (worstIndex != -1) {
            cout << "Request " << requests[i] << " allocated to block " << worstIndex << "\n";
            blocks[worstIndex] -= requests[i];
        } else {
            cout << "Request " << requests[i] << " could not be allocated.\n";
        }
        printMemory(blocks, m);
    }
}

int main() {
    int m, n;

    cout << "Enter the number of memory blocks: ";
    cin >> m;
    int blocks[m];
    cout << "Enter the sizes of the memory blocks:\n";
    for (int i = 0; i < m; ++i) {
        cin >> blocks[i];
    }

    cout << "Enter the number of requests: ";
    cin >> n;
    int requests[n];
    cout << "Enter the sizes of the requests:\n";
    for (int i = 0; i < n; ++i) {
        cin >> requests[i];
    }

    int blocksCopy[m];

    copy(blocks, blocks + m, blocksCopy);
    firstFit(blocksCopy, m, requests, n);

    copy(blocks, blocks + m, blocksCopy);
    nextFit(blocksCopy, m, requests, n);

    copy(blocks, blocks + m, blocksCopy);
    bestFit(blocksCopy, m, requests, n);

    copy(blocks, blocks + m, blocksCopy);
    worstFit(blocksCopy, m, requests, n);

    return 0;
}
