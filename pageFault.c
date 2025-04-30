#include<stdio.h>
#include<stdlib.h>

int fifo(int pages[],int n,int m){
     int frames[m];
     for(int i=0;i<m;i++){
         frames[i]=-1;//Initially all pages are empty
     }

     printf("ID \t");
     printf("Frames \t");
     printf("Page Fault\t\n");

     int page_faults=0;
     int next_frame=0;

     for(int i=0;i<n;i++){
         int current_page=pages[i];
         int found=0;
         for(int j=0;j<m;j++){
            if(frames[j]==current_page){
                found=1;
                break;
            }
        }
        if(found==0){
         frames[next_frame]=current_page;
         next_frame=(next_frame+1)%m;
         page_faults++;
          printf("%d\t",current_page);
             for(int j=0;j<m;j++){
               if(frames[j]==-1){
                printf("- ");
             }
             else{
                printf("%d ",frames[j]);
             }
         }
         printf("\t YES\n");
     }
     else {
         printf("%d\t",current_page);
         for(int i=0;i<m;i++){
            if(frames[i]==-1){
                 printf("- ");
            }
            else {
                printf("%d ",frames[i]);
            }

         }
         printf("\t NO \n");
     }
   }
   return page_faults;       
}  

int main(){
       int n;
       
       printf("Enter the no.of pages\n");
       scanf("%d",&n);
       int pages[n];
       
       printf("Enter the Page.no\n");
         for(int i=0;i<n;i++){
             int id;
             scanf("%d",&id);
             pages[i]=id;
         } 

       int frames;
       printf("Enter the no.of frames\n");
       scanf("%d",&frames);
       int fifo_faults=fifo(pages,n,frames);
       printf("\n The Percentage of Page Faults is==%.2f\n",fifo_faults/(double)n);
       return 0;
}