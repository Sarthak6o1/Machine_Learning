#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

sem_t r,w;
int shared_data=0;
int read_cnt=0;

void *reader(void *arg){
    while(1){
    int id=*(int*)arg;
    sem_wait(&r);
    if(read_cnt==0){
        sem_wait(&w);
    }
    read_cnt++;
    sem_post(&r);
    
    printf("Reader %d is reading. Shared Data: %d\n", id, shared_data);
    
    sem_wait(&r);
    read_cnt--;
    if(read_cnt==0){
        sem_post(&w);
    }
    sem_post(&r);
    }
}

void *writer(void *arg){
     while(1){
      int id=*(int *)arg;
      sem_wait(&w);
      shared_data+=10;
      printf("Writer %d is writing .Shared Data:%d\n",id,shared_data);
      sem_post(&w);
     }
}
int main(){
       pthread_t readers[5],writers[2];
       int readersId[5]={1,2,3,4,5};
       int writersId[2]={1,2};
       
       sem_init(&r,0,1);
       sem_init(&w,0,1);

       for( int i=0;i<5;i++){
         pthread_create(&readers[i],NULL,reader,&readersId[i]);
       }
       for( int i=0;i<2;i++){
        pthread_create(&writers[i],NULL,writer,&writersId[i]);
      }
      for( int i=0;i<5;i++){
        pthread_join(readers[i],NULL);
      }
      for( int i=0;i<2;i++){
        pthread_join(writers[i],NULL);
      }

      
      return 0;
}