#include <stdio.h>
#include<stdbool.h>
int main() {
  int n, m;
  printf("Enter Numbe rof Process: ");
  scanf("%d", &n);
  printf("Enter Number of Resources: ");
  scanf("%d", &m);

  int allocation[n][m], available[m], finish[n], request[n][m];
  printf("Enter NUmber of Allocation \n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &allocation[i][j]);
    }
  }

  printf("Enter Request Matrix ");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d",&request[i][j]);
    }
  }

  printf("Available MAtrix\n");
  for(int i=0;i<m;i++){
    scanf("%d",&available[i]);
  }

  printf("Initializing Finsh array\n");
  for(int i=0;i<n;i++){
    finish[i]=0;
  }

  printf("Deting if any deadlock");
  int deadlock=0;
  for(int count=0;count<n;count++){
    bool any_process_finish = false;
    for(int i =0;i<n;i++){
      bool can_finish = true;
      for(int j=0;j<m;j++){
        if(request[i][j]>available[j]){
          can_finish=false;
          break;
        }  
      
      if(can_finish){
        for(int j=0;j<n;j++){
          available[j]+=allocation[i][j];
        }
        finish[i]=1;
        any_process_finish = true;
        break;
      }
    }}
    if(!any_process_finish){
      deadlock = 1;
      break;
    }
  }  
  if(deadlock){
    printf(" System is in dead lock \nDEdlock Processed");
    for(int i =0 ;i<n;i++){
      if(!finish[i]){
        printf("p%d",i);
      }
    }
  }
    else{
      printf("NO deadlock detected");
    }
    return 0;
  }

