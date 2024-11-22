#include <stdio.h>
#include <stdlib.h>
int main() {
  int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
  int n = sizeof(requests) / sizeof(requests[0]);
  int head = 50;
  int totalSeekTime = 0;
  printf("FCFS Disk Sheduling:\n ");
  for (int i = 0; i < n; i++) {
    printf("Head moves from %d to %d\n", head, requests[i]);
    totalSeekTime += abs(requests[i] - head);
    head = requests[i];
  }
  printf("Total Seek Time %d", totalSeekTime);
  return 0;
}
