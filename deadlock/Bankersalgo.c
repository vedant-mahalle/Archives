#include <stdio.h>

int main() {
  int n, m, i, j, k;
  printf("Enter the number of process:");
  scanf("%d", &n);
  printf("Enter the number of resources");
  scanf("%d", &m);

  int safeSequence[n], index = 0, available[m], max[n][m], allocation[n][m],
                       need[n][m], finish_process[n];
  printf("Enter ALlocation Matrix\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &allocation[i][j]);
    }
  }
  printf("ENter Max Matrix\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &max[i][j]);
    }
  }

  printf("Enter Available Matrix\n");
  for (int i = 0; i < m; i++) {
    scanf("%d", &available[i]);
  }

  printf("Getting Need MAtrix\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = max[i][j] - allocation[i][j];
      printf("%d ", need[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < n; i++) {
    finish_process[i] = 0;
  }

  int total_exexuted_process=0;
  while (total_exexuted_process < n) {
    int any_process_found = 0;
    for (int i = 0; i < n; i++) {
      if (finish_process[i] == 0) {
        int can_be_executed = 1;
        for (int j = 0; j < m; j++) {
          if (need[i][j] > available[j]) {
            can_be_executed = 0;
            break;
          }
        }
        if (can_be_executed) {
          for (int j = 0; j < n; j++) {
            available[j] = available[j] + allocation[i][j];
          }
          safeSequence[index++] = i;
          finish_process[i] = i;
          total_exexuted_process++;
          any_process_found = 1;
          printf("\nProcess P%d is executing\n", i);
          printf("Update available resources\n");
          for (int j = 0; j < m; j++) {
            printf("%d ", available[j]);
          }
          printf("\n");
        }
      }
    }
    if (!any_process_found) {
      printf("The system is not in a safe sequence\n");
      return 0;
    }
  }
  printf(
      "THe system has reached the safe state.\nSafe sequence execution is\n");
  for (int i = 0; i < n; i++) {
    printf("P%d->", finish_process[i]);
  }
  return 0;
}
