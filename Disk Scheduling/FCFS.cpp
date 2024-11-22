#include <bits/stdc++.h>
using namespace std;

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

    int totalSeek = 0;

    cout << "Current Position | Request | Seek Time\n";
    cout << "-----------------|---------|-----------\n";

    for (int i = 0; i < n; i++) {
        cout << setw(17) << head << " | " << requests[i] << " | " 
             << abs(requests[i] - head) << endl;
        totalSeek += abs(requests[i] - head);
        head = requests[i];
    }

    cout << "Total seek time: " << totalSeek << endl;

    return 0;
}
