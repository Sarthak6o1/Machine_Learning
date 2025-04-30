#include<stdio.h>
#include<stdlib.h>
struct process{
     char pId[5];
     int at;
     int bt;
     int ct;
     int tat;
     int wat;   
};
void rr(struct process p[],int n,int quantum){
     int total_tat=0,total_wat=0; 
    for(int i=0;i<n-1;i++){
         for(int j=0;j<n-1-i;j++){
             if(p[j].at>p[j+1].at){
                 struct process temp=p[j];
                 p[j]=p[j+1];
                 p[j+1]=temp;
             }
         }
    }
     int rem[5]={0};
     int time=0;   
     int completed=0;
     int idx=0;
     int q[5]={0};
     int front=0,rear=0;

     for(int i=0;i<n;i++){
          rem[i]=p[i].bt;
        }
     while(idx<n && p[idx].at<=time){
        q[rear++]=idx++;
     }
     while(completed<n){
         if(front == rear){
             time=p[idx].at;
             q[rear++]=idx++;

         }
         int i=q[front++];
         if(rem[i]>quantum){
             rem[i]-=quantum;
             time+=quantum;
         }
         else{
            time+=rem[i];
            rem[i]=0; 
        }
         while(idx<n && p[idx].at<=time){
             q[rear++]=idx++;
         }
         if(rem[i]>0){
             q[rear++]=i;
         }
         else{
            p[i].ct=time;
            p[i].tat=p[i].ct-p[i].at;
            p[i].wat=p[i].tat-p[i].bt;
            completed++;
            total_tat += p[i].tat;
            total_wat  += p[i].wat;
         }
     }
     printf("\nProper Round Robin Scheduling (Time Quantum = %d):\n", quantum);
     printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
     printf("Average Waiting Time:    %.2f\n", (float)total_wat  / n);
         

}
int main(){

    struct process P[5] = {
        {"P1", 0, 3},
        {"P2", 1, 2},
        {"P3", 2, 4},
        {"P4", 3, 5},
        {"P5", 4, 1}
    };
    rr(P,5,2);
      return 0;
}