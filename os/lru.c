#include<stdio.h>
#include<stdlib.h>
 
void lru(int pages[],int n,int m){
       int frames[m];
       int recent[m];
       for(int i=0;i<m;i++){
         frames[i]=-1;
         recent[i]=0;
       }
       for(int i=0;i<n;i++){
         int curr_page=pages[i];
         int found=0;
         for(int j=0;j<m;j++){
             if(frames[j]==pages[i]){
                found=1;
                recent[j]=i;
                break; 
             }

         }

         if(!found){
            int empty_frame=0;
            for(int j=0;j<m;j++){
                 if(frames[j]==-1){
                    frames[j]=curr_page;
                    empty_frame=1;
                    recent[j]=i;
                    break;
                 }
            }
            if(!empty_frame){
                 int min=recent[0];
                 int pos=0;
                 
                for(int j=0;j<m;j++){
                  if(recent[j]<min){
                    pos=j;
                    min=recent[j];
                  }
                }
               frames[pos]=curr_page;
               recent[pos]=i;
            }
         }
         printf("%d\t", curr_page);
         for(int j = 0; j < m; j++) {
             if(frames[j] == -1) {
                 printf("- ");
             } else {
                 printf("%d ", frames[j]);
             }
         }
         printf("\t\t%s\n", found ? "No" : "Yes");
        }
   }


int main(){
     int pages[10]={4,5,6,56,5,6,7,8,7,9};
     int m;
     printf("Enter the size of frame \n");
     scanf("%d",&m);

     lru(pages,10,m);
     
     return 0;
}