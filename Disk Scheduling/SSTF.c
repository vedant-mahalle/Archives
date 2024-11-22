#include <stdio.h>
#include <stdlib.h>

void SSTF(int head1, int no_req, int disc_req[]) {
    int min, diff;
    int pending = no_req;
    int distance = 0, index;
    int finish[no_req], head = head1;

    for (int i = 0; i < no_req; i++) {
        finish[i] = 0; // Mark all requests as unfinished
    }

    printf("\nSequence of head movements:\n%d -> ", head);

    while (pending > 0) {
        min = 999; // Large value to find the minimum
        for (int i = 0; i < no_req; i++) {
            diff = abs(head - disc_req[i]);
            if (finish[i] == 0 && diff < min) {
                min = diff;
                index = i;
            }
        }
        finish[index] = 1; // Mark request as completed
        distance += abs(head - disc_req[index]);
        head = disc_req[index];
        pending--;
        printf("%d -> ", head);
    }

    printf("\nTotal Distance Traversed: %d\n", distance);
}

int main() {
    int head = 50; // Initial head position
    int no_req = 8; // Number of disk requests
    int disc_req[] = {176, 79, 34, 60, 92, 11, 41, 114}; // Disk requests

    SSTF(head, no_req, disc_req);

    return 0;
}
