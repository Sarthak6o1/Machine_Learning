#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rd,wrt;
int read_cnt=0;
int shared_data=0;

void *read(void *arg){
     int id=*((int*)arg);
     while(1){
         sem_wait(&rd);
         if(read_cnt==0){
            sem_wait(&wrt);
        }
            read_cnt++;
            sem_post(&rd);

            printf("Reader %d is reading. Shared Data: %d\n", id, shared_data);

            sem_wait(&rd);
            read_cnt--;
            if(read_cnt==0){
                 sem_post(&wrt);
            }
            sem_post(&rd);
     }
}

void *write(void *arg){
      int id=*((int *)arg);
      while(1){
         sem_wait(&wrt);

         shared_data+=10;
         printf("Writer %d is writing .Shared Data:%d\n",id,shared_data);
        
         sem_post(&wrt);
      }
}

int main(){
     pthread_t readers[5],writers[2];

     int readersId[5]={1,2,3,4,5};
     int writersId[5]={1,2};

     sem_init(&rd,0,1);
     sem_init(&wrt,0,1);

     for(int i=0;i<5;i++){
         pthread_create(&readers[i],NULL,read,&readersId[i]);
     }
      for(int i=0;i<2;i++){
         pthread_create(&writers[i],NULL,write,&writers[i]);
        }

        for(int i=0;i<5;i++){
             pthread_join(readers[i],NULL);
        }
        for(int i=0;i<2;i++){
             pthread_join(writers[i],NULL);
        }

        sem_destroy(&rd);
        sem_destroy(&wrt);
      return 0;
}