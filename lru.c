#include<stdio.h>
#include<stdlib.h>

void lru(int pages[],int n,int m){
     int frame[m];
     int recent[m];
    for(int i=0;i<m;i++){
         frame[i]=-1;
          recent[i]=0;

      }
      for(int i=0;i<n;i++){
        int page=pages[i];
        int found=0; 
         for(int j=0;j<m;j++){
             if(frame[j]==pages[i]){
                recent[j]++;
                found=1;
                 break;
                 
             }
         }
         if(!found){
            int empty_frame;
          for(int i=0;i<m;i++){
            empty_frame=0;
            if(frame[i]==-1){
                frame[i]=page;
                empty_frame++;
                recent[i]++;
                break;
            }

          }
          if(!empty_frame){
            int min=recent[0];
            int pos=0;;
             for(int i=0;i<m;i++){
                 if(recent[i]<min){
                    min=recent[i];
                    pos=i;
                 }
             }
              frame[pos]=page;
              recent[pos]++;   
              
          
            }
         }
         printf("%d\t", page);
         for(int j = 0; j < m; j++) {
             if(frame[j] == -1) {
                 printf("- ");
             } else {
                 printf("%d ", frame[j]);
             }
         }
         printf("\t\t%s\n", found ? "No" : "Yes");
     } 

    }
int main(){
     int n;
     printf("Enter the no.of pages\n");
     scanf("%d",&n);
     
     int m;
     printf("Enter the no.of frames\n");
     scanf("%d",&m);

     int pages[n];

     for(int i=0;i<n;i++){
        int val;
        printf("Enter Page Id\n");
        scanf("%d",&val);
        pages[i]=val;
     }
     lru(pages,n,m);

     
      return 0;
}