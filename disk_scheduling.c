#include <stdio.h>
#include <stdlib.h>

int scan_scheduling(int scan[],int n,int head){
    
     int tot_scan=0;
      for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
             if(scan[j]>scan[j+1]){
                 int temp=scan[j];
                 scan[j]=scan[j+1];
                 scan[j+1]=temp;
             }
        }
      }
      int pos=0;
      for(int i=0;i<n;i++){
        if(scan[i]>=head){
            pos=i;
            break;
        }
      }
      for(int i=pos-1;i>=0;i--){
        tot_scan+=abs(head-scan[i]);
        head=scan[i];
     }
      tot_scan+=abs(0-head);
      head=0;
      for(int i=pos;i<n;i++){
        tot_scan+=abs(scan[i]-head);
        head=scan[i];

     }
  return tot_scan;


}

int fcfs_scheduling(int fcfs[],int n,int head){
    int tot_fcfs=0;
    for(int i=0;i<n;i++){
        tot_fcfs+=abs(fcfs[i]-head);
        head=fcfs[i];
       }

      return tot_fcfs; 
}

int main(){
       int fcfs[10];
       int n;
       printf("Enter the no.of process\n");
       scanf("%d",&n);
       for(int i=0;i<n;i++){
          int val;
          printf("Enter the value of process\n"); 
          scanf("%d",&val);
          fcfs[i]=val;
       }
       int head;
       printf("Enter the Head of The Disk\n");
       scanf("%d",&head);
       int tot_fcfs=fcfs_scheduling(fcfs,n,head);
       printf("The total seek time for first come first serve is: %d\n",tot_fcfs);
       
       int scan[10];
       int m;
       printf("Enter the no.of process for scan algo");
       scanf("%d",&m);

       for(int i=0;i<m;i++){
        int val;
        printf("Enter the value of the process\n");
        scanf("%d",&val); 
        scan[i]=val;
       }

       int head2;
       printf("Enter the value of head\n");
       scanf("%d",&head2);
       int tot_scan=scan_scheduling(scan,m,head2);
       printf("Total seek time for scan algo is %d\n",tot_scan);
return 0;

}