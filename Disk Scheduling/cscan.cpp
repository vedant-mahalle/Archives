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

    int totalSeek = 0;

    sort(requests.begin(), requests.end());

    int nextReq = upperBound(requests, head);
    bool rev = false;


    cout << "Current Position | Request | Seek Time\n";
    cout << "-----------------|---------|-----------\n";
    if (nextReq == -1) {
        rev = true;
        cout << "Seek moves from " << head << " to " << diskEnd << endl;
        totalSeek+=abs(diskEnd-head);
        head = diskEnd;
        cout << setw(17) << head << " | " << diskStart << " | " << abs(diskStart - head) << endl;
        totalSeek+=abs(head-diskStart);
        head = diskStart;
        nextReq = 0; 
    }


    for (int i = 0; i < n; i++) {
        int idx = (nextReq + i) % n;  
        cout << setw(17) << head << " | " << requests[idx] << " | " << abs(requests[idx] - head) << endl;
        totalSeek+=abs(requests[idx] - head);
        head = requests[idx]; 

        if(nextReq+i==n-1 && !rev){
            cout << setw(17) << head << " | " << diskEnd << " | " << abs(diskEnd - head) << endl;
            totalSeek+=abs(diskEnd-head);
            head = diskEnd;
            cout << setw(17) << head << " | " << diskStart << " | " << abs(diskStart - head) << endl;
            totalSeek+=abs(diskStart-head);
            head = diskStart;
        }
    }

    cout<<"Total seek time "<<(float)totalSeek/n<<endl;

    return 0;
}
