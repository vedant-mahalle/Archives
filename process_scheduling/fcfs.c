#include <stdio.h>

int main() {
  int nprocess;
  printf("Enter Number of Process");
  scanf("%d", &nprocess);
  int at[nprocess],tat[nprocess],ct[nprocess], bt[nprocess],wt[nprocess];
  printf("Enter arrival time for all process");
  for (int i = 0; i < nprocess; i++) {
    scanf("%d", &at[i]);
  }

  printf("Enter burst time for all process");
  for (int i = 0; i < nprocess; i++) {
    scanf("%d", &bt[i]);
  }

  printf(" calculating completion time");
  ct[0]=at[0]+bt[0];
  for(int i =1 ;i<nprocess;i++){
    if(ct[i]<at[i]){
      ct[i]=at[i]+bt[i];
    }
    else{
      ct[i]=ct[i-1] + bt[i];
    }
  }
  printf("Calculating Total turn arond time\n");
  for(int i=0;i<nprocess;i++){
    tat[i]=ct[i]-at[i];
  }
  
  printf("Calculating waiting turn arond time\n");
  for(int i=0;i<nprocess;i++){
    wt[i]=tat[i]-bt[i];
  }
  printf("\nProcess\tArrival\tBurstTIme\tcompletion\tTat\tWaiting Time\n");
  for(int i=0;i<nprocess;i++){
    printf("\nP%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
  }
}
