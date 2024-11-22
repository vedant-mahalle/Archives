
#include <stdio.h>
#include <stdlib.h>

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

    // Sort requests array
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

    // Move to the right
    for (int i = nextReq; i < n; i++) {
        printf("%17d | %7d | %9d\n", head, requests[i], abs(requests[i] - head));
        totalSeek += abs(requests[i] - head);
        head = requests[i];
    }

    // Move to the disk end
    if (head != diskEnd) {
        printf("%17d | %7d | %9d\n", head, diskEnd, abs(diskEnd - head));
        totalSeek += abs(diskEnd - head);
        head = diskEnd;
    }

    // Move to the left
    for (int i = nextReq - 1; i >= 0; i--) {
        printf("%17d | %7d | %9d\n", head, requests[i], abs(requests[i] - head));
        totalSeek += abs(requests[i] - head);
        head = requests[i];
    }

    printf("Total seek time: %d\n", totalSeek);

    return 0;
}
