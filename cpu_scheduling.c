#include<stdio.h>
#include<stdlib.h>

struct process{
    int pId;
    int arrivalTime;
    int burstTime;
    int startTime;
    int completionTime;
    int TAT;
    int WAT;
};
void fcfs(struct process p[],int n){
     for(int i=0;i<n;i++){
         for(int j=0;j<n-1-i;j++){
             if(p[j].arrivalTime>p[j+1].arrivalTime){
                struct process temp=p[j];
                p[j+1]=p[j];
                p[j]=temp;
             }
         }
        }
         p[0].startTime=0;
     for(int i=1;i<n;i++){
            p[i].startTime=p[i-1].startTime+p[i-1].burstTime;
     }
         for(int i=0;i<n;i++){
            p[i].completionTime=p[i].startTime+p[i].burstTime;
            p[i].TAT=p[i].completionTime-p[i].arrivalTime;
            p[i].WAT=p[i].TAT-p[i].burstTime;
         }
     printf("Arrival Burst Start Completion TAT WAT \n");
     for(int i=0;i<n;i++){
          printf("%d \t %d \t %d \t %d\t % d\t %d \t \n",p[i].arrivalTime,p[i].burstTime,p[i].startTime,p[i].completionTime,p[i].TAT,p[i].WAT);
     }
}
void sjf_nonpreemptive(struct process p[], int n) {
    // Sort by arrival time first
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].arrivalTime > p[j+1].arrivalTime) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    for(int i = 0; i < n; i++) {
        // Find shortest job among arrived processes
        int min_burst_index = i;
        for(int j = i; j < n; j++) {
            if(p[j].arrivalTime <= current_time && 
               p[j].burstTime < p[min_burst_index].burstTime) {
                min_burst_index = j;
            }
        }

        // Handle idle time if no process has arrived
        if(p[min_burst_index].arrivalTime > current_time) {
            current_time = p[min_burst_index].arrivalTime;
        }

        // Swap processes
        struct process temp = p[i];
        p[i] = p[min_burst_index];
        p[min_burst_index] = temp;

        // Calculate process timings
        p[i].startTime = current_time;
        p[i].completionTime = current_time + p[i].burstTime;
        p[i].TAT = p[i].completionTime - p[i].arrivalTime;
        p[i].WAT = p[i].TAT - p[i].burstTime;

        current_time = p[i].completionTime;
    }

    // Print results
    printf("\nProcess | Arrival | Burst | Start | Completion | TAT | WAT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t| %d\t| %d\t| %d\t| %d\t\t| %d\t| %d\n", 
               p[i].pId, p[i].arrivalTime, p[i].burstTime,
               p[i].startTime, p[i].completionTime, p[i].TAT, p[i].WAT);
    }
}
int main(){
      int n;
      printf("Enter the no.of Processes\n");
      scanf("%d",&n);
      struct process process[n];
      for(int i=0;i<n;i++){
         int id=0;
         process[i].pId=id++;
         printf("Enter the arrival time of process\n");
         int arrivalTime;
         scanf("%d",&arrivalTime);
         process[i].arrivalTime=arrivalTime;
         printf("Enter the burst time of process\n");
         int burstTime;
         scanf("%d",&burstTime);
         process[i].burstTime=burstTime;
        }
        fcfs(process,n);
        sjf_nonpreemptive(process,n);
     
      return 0;
}