#include <stdio.h>
#include <stdlib.h>

void nextFit(int memoryBlock[], int m, int processBlock[], int n) {
  int allocation[n];
  for (int i = 0; i < n; i++) {
    allocation[i] = -1;
  }
  int last_allocation = 0;
  for (int i = 0; i < n; i++) {
    int j = last_allocation;
    do {
      if (memoryBlock[j] >= processBlock[i]) {
        allocation[i] = j;
        memoryBlock[j] -= processBlock[i];
        last_allocation = j;
      }
        j=(j+1)%m;
    }while(j!=last_allocation);
  } 
    printf("\nNext Fit Allocation\n");
    printf("Process No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i + 1, processBlock[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
  int memoryblock[] = {100, 500, 200, 300, 600}; // Example memory blocks
  int processblock[] = {212, 417, 112, 426};     // Example process blocks
  int n = sizeof(memoryblock) / sizeof(memoryblock[0]);
  int m = sizeof(processblock) / sizeof(processblock[0]);
  nextFit(memoryblock, n, processblock, m);
  return 0;
}
