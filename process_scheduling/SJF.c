#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  printf("Enter Number of Process: ");
  scanf("%d", &n);

  int at[n], bt[n], ct[n], wt[n], tat[n], isCompleted[n], currentTime = 0,
                                                          completed = 0;

  printf("Enter arrival time for all process");
  for (int i = 0; i < n; i++) {
    scanf("%d", &at[i]);
  }

  printf("Enter burst time for all process");
  for (int i = 0; i < n; i++) {
    scanf("%d", &bt[i]);
  }
  for (int i = 0; i < n; i++) {
    isCompleted[i] = 0;
  }

  while (completed < n) {
    int minIndex = -1, minBT = 999;
    for (int i = 0; i < n; i++) {
      if (at[i] <= minBT && !isCompleted[i] && bt[i] < minBT) {
        minBT = bt[i];
        minIndex = i;
      }
      if (minIndex == -1) {
        currentTime++;
      } else {
        currentTime += bt[minIndex];
        ct[minIndex] = currentTime;
        tat[minIndex] = ct[minIndex] - at[minIndex];
        wt[minIndex] = tat[minIndex] - bt[minIndex];
        isCompleted[minIndex] = 1;
        completed++;
      }
    }
}
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
      printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i],
             wt[i]);

    return 0;
  
}
