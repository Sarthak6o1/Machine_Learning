#include<stdio.h>
#include<stdlib.h>
void scan(int process[],int n,int head){
     int tot=0;
      for(int i=0;i<n-1;i++){
         for(int j=0;j<n-i-1;j++){
             if(process[j]>process[j+1]){
                 int temp=process[j];
                 process[j]=process[j+1];
                 process[j+1]=temp;
             }
         }
      }
      int pos=0;
      for(int i=0;i<n;i++){
         if(process[i]>=head){
             pos=i;
             break;
         }
     }

     for(int i=pos-1;i>=0;i--){
         tot+=abs(process[i]-head);
         head=process[i];
        }
     tot+=abs(head-0);
     head=0;
     for(int i=pos;i<n;i++){
         tot+=abs(process[i]-head);
         head=process[i];
     }

     printf("Tot distance = %d",tot);
}

int main(){  
    int process[8]={56,78,67,134,96,34,123,178};
    int head=53;
    scan(process,8,head);
     
    return 0;
}