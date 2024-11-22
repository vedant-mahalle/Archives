#include <bits/stdc++.h>
using namespace std;

int upperBound(vector<int>& requests, int head) {
    int low = 0, high = requests.size() - 1;
    int res = -1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (requests[mid] >= head) {
            res = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return res;
}

int main() {
    int head, n, diskStart, diskEnd;

    cout << "Enter the current head position: ";
    cin >> head;

    cout << "Enter the number of requests: ";
    cin >> n;

    cout << "Enter the starting disk position: ";
    cin >> diskStart;

    cout << "Enter the ending disk position: ";
    cin >> diskEnd;

    vector<int> requests(n);
    cout << "Enter the requests (space-separated): ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    sort(requests.begin(), requests.end());

    int totalSeek = 0;
    int nextReq = upperBound(requests, head);  
    bool reverse = false;

    cout << "Current Position | Request | Seek Time\n";
    cout << "-----------------|---------|-----------\n";

    for (int i = nextReq; i < n; i++) {
        cout << setw(17) << head << " | " << requests[i] << " | " 
             << abs(requests[i] - head) << endl;
        totalSeek += abs(requests[i] - head);
        head = requests[i];
    }

    if (head != diskEnd) {
        cout << setw(17) << head << " | " << diskEnd << " | " 
             << abs(diskEnd - head) << endl;
        totalSeek += abs(diskEnd - head);
        head = diskEnd;
    }

    for (int i = nextReq - 1; i >= 0; i--) {
        cout << setw(17) << head << " | " << requests[i] << " | " 
             << abs(requests[i] - head) << endl;
        totalSeek += abs(requests[i] - head);
        head = requests[i];
    }

    cout << "Total seek time: " << totalSeek << endl;

    return 0;
}
