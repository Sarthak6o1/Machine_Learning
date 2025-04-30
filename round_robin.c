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
void sort(struct process p[],int n, int q){
       for(int i=0;i<n;i++){
         for(int j=0;j<n-1-i;j++){
            if(p[j].arrivalTime>p[j+1].arrivalTime){
                struct process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
         }
       }
}
void round_robin(struct process p[],int n,int q){
      int completed=0;
      int currentTime=0;
      sort(p,n,q);
      while(completed<n){
         for(int i=0;i,n;i++){
            if(p[i].arrivalTime<=currentTime ){
                if(p[i].burstTime>=q){
                currentTime+=q;
                p[i].burstTime-q;
                i=(i+1)%n;
                }
                else{
                    currentTime+=p[i].burstTime;
                    p[i].burstTime=0;
                    i=(i+1)%n;
                    completed++;
                    p[i].completionTime+=currentTime;
                    p[i].TAT=p[i].completionTime-p[i].arrivalTime;
                    p[i].WAT=p[i].TAT-p[i].burstTime;
                }
            }
        }
          


      }
      printf("\nProcess\tArrival\tBurst\tStart\tCompletion\tTAT\tWAT\n");
         for(int i = 0; i < n; i++) {
            printf("%d\t%d\t%d\t%d\t%d\t\t%d\t%d\n", 
            i, p[i].arrivalTime, p[i].burstTime, p[i].startTime,
           p[i].completionTime, p[i].TAT, p[i].WAT);
}

}
int main(){
     printf("Enter the no.of processes\n");
     int n;
     scanf("%d",&n);
     printf("Enter the time-quantum\n");
     int q;
     scanf("%d",&q);   
     struct process p[n]; 
     for(int i=0;i<n;i++){
         int arr;
         printf("Enter the arrival time\n");
         scanf("%d",&arr);
         p[i].arrivalTime=arr;
         int bt;
         printf("Enter the burst time\n");
         scanf("%d",&bt);
         p[i].burstTime=bt;

     }
     round_robin(p,n,q);
     return 0;
}