#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void bankers(int alloc[][3],int max[][3],int avail[]){
     int need[5][3]={0}; 
     for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
     int safe[5]={0};
     int complete=0;
     bool finish[5]={false};
        while(complete<5){
         bool canAllocate=false;
        for(int i=0;i<5;i++){
            if(!finish[i]){
              int j;
              for(j=0;j<3;j++){
                 if(need[i][j]>avail[j])
                 break;
              }
              if(j==3){
                 for(int j=0;j<3;j++){
                  avail[j]+=alloc[i][j];
                 }
                 safe[complete]=i;
                 complete++;
                 canAllocate=true;
                 finish[i]=true;
              }
            }
        }
        if(!canAllocate){
            printf("No safe sequence found\n");
            return;
        }
   }
       printf("Safe sequnce detected\n");
       for(int i=0;i<5;i++){
          printf("%d-->",safe[i]); 
       }


     
}

int main(){
    int alloc[5][3]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[5][3]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int avail[3]={3,3,2};

    bankers(alloc,max,avail);
     return 0;
}