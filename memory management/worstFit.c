#include <stdio.h>

void bestFit(int memoryblock[], int m, int processblock[], int n) {
  int allocation[n];
  for (int i = 0; i < n; i++) {
    allocation[i] = -1;
  }
  for (int i = 0; i < n; i++) {
    int worstIndx = -1;
    for (int j = 0; j < m; j++) {
      if (memoryblock[j] >= processblock[i]) {
        if (worstIndx == -1 || memoryblock[worstIndx] <= memoryblock[j]) {
          worstIndx = j;
        }
      }
    }
    if (worstIndx != -1) {
      allocation[i] = worstIndx;
      memoryblock[worstIndx] -= processblock[i];
    }
  }
  printf("\nBest Fit Allocation\n");
  for (int i = 0; i < n; i++) {
    if (allocation[i] != -1) {
      printf("Process %d allocated to memory block %d\n", i + 1,
             allocation[i] + 1);
    } else {
      printf("Process %d not allocated\n", i + 1);
    }
  }
}

int main() {
  int memoryblock[] = {100, 500, 200, 300, 600}; // Example memory blocks
  int processblock[] = {212, 417, 112, 426};     // Example process blocks
  int n = sizeof(memoryblock) / sizeof(memoryblock[0]);
  int m = sizeof(processblock) / sizeof(processblock[0]);
  bestFit(memoryblock, n, processblock, m);
  return 0;
}
