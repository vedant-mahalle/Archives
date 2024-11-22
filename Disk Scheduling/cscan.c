
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int upperBound(int requests[], int n, int head) {
    int low = 0, high = n - 1, res = -1;
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

    printf("Enter the current head position: ");
    scanf("%d", &head);

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the starting disk position: ");
    scanf("%d", &diskStart);

    printf("Enter the ending disk position: ");
    scanf("%d", &diskEnd);

    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Sort the requests array
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int totalSeek = 0;
    int nextReq = upperBound(requests, n, head);

    printf("Current Position | Request | Seek Time\n");
    printf("-----------------|---------|-----------\n");

    if (nextReq == -1) { 
        // Move to disk end and then to start
        printf("%17d | %7d | %9d\n", head, diskEnd, abs(diskEnd - head));
        totalSeek += abs(diskEnd - head);
        head = diskEnd;

        printf("%17d | %7d | %9d\n", head, diskStart, abs(diskStart - head));
        totalSeek += abs(diskStart - head);
        head = diskStart;

        nextReq = 0;
    }

    for (int i = 0; i < n; i++) {
        int idx = (nextReq + i) % n;
        printf("%17d | %7d | %9d\n", head, requests[idx], abs(requests[idx] - head));
        totalSeek += abs(requests[idx] - head);
        head = requests[idx];

        // Handle wrap-around from end to start
        if (nextReq + i == n - 1) {
            printf("%17d | %7d | %9d\n", head, diskEnd, abs(diskEnd - head));
            totalSeek += abs(diskEnd - head);
            head = diskEnd;

            printf("%17d | %7d | %9d\n", head, diskStart, abs(diskStart - head));
            totalSeek += abs(diskStart - head);
            head = diskStart;
        }
    }

    printf("Total seek time: %.2f\n", (float)totalSeek / n);
    return 0;
}
