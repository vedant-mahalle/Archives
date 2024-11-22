#include <bits/stdc++.h>
using namespace std;

int findClosestRequest(vector<int>& requests, int head, vector<bool>& visited) {
    int minDistance = INT_MAX;
    int closestIndex = -1;

    for (int i = 0; i < requests.size(); i++) {
        if (!visited[i] && abs(requests[i] - head) < minDistance) {
            minDistance = abs(requests[i] - head);
            closestIndex = i;
        }
    }
    return closestIndex;
}

int main() {
    int head, n;

    cout << "Enter the current head position: ";
    cin >> head;

    cout << "Enter the number of requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the requests (space-separated): ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    vector<bool> visited(n, false); 
    int totalSeek = 0;

    cout << "Current Position | Request | Seek Time\n";
    cout << "-----------------|---------|-----------\n";

    for (int i = 0; i < n; i++) {
        int closestIndex = findClosestRequest(requests, head, visited);
        if (closestIndex == -1) break; 

        cout << setw(17) << head << " | " << requests[closestIndex] 
             << " | " << abs(requests[closestIndex] - head) << endl;

        totalSeek += abs(requests[closestIndex] - head);
        head = requests[closestIndex];
        visited[closestIndex] = true; 
    }

    cout << "Total seek time: " << totalSeek << endl;

    return 0;
}
