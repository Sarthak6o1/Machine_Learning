#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void bankers(int alloc[][3],int max[][3],int avail[]){
      bool finish[5]={false};
      int work[5]={0};
      int safeSeq[5]={0};
      int need[5][3]={0}; 
      int count=0;
      
      for(int i=0;i<5;i++){
       for(int j=0;j<3;j++){
          need[i][j]=max[i][j]-alloc[i][j];
          
        }
    } 
    for(int j=0;j<3;j++){
        work[j]=avail[j];
    } 
    while(count<5){
      bool found=false;
     for(int i=0;i<5;i++){
        if(!finish[i]){
       int j;
         for( j=0;j<3;j++){
         if(need[i][j]>work[j]){
            break;
         }
      }
           if(j==3){
            for(int j=0;j<3;j++){
               work[j]+=alloc[i][j];
            }
            finish[i]=true;
            safeSeq[count++]=i;
            found=true;
            break;
           }
     }  
  }  
    if(!found){
       printf("Unsafe State\n");
    }  
}
         
         printf("System is in safe state.\nSafe sequence is: ");
         for (int i = 0; i <5; i++) {
         printf("P%d ", safeSeq[i]);
         }
         printf("\n");

         }
int main(){
     int alloc[5][3]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
     int max[5][3]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
     int avail[3]={3,3,2};

     bankers(alloc,max,avail);


     return 0;
}