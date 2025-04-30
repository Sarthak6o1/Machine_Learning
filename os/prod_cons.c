#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
pthread_mutex_t lock ;
struct BUFF{
      int full;
      int empty;
};
void *th2(void *args){ 
    while(1){
        struct  BUFF *buffer = (struct BUFF *)args;
        pthread_mutex_lock(&lock);
        if(buffer->full!=5){
             buffer->full++;
             buffer->empty--;
        printf("buffer full is is:- %d\n", buffer->full);
        printf("buffer empty is is:- %d\n", buffer->empty);

      }
      pthread_mutex_unlock(&lock);
}
}
void *th1(void *args){ 
    while(1){
        struct  BUFF *buffer= (struct BUFF *)args;
        pthread_mutex_lock(&lock);
        if(buffer->empty!=5){
             buffer->full--;
             buffer->empty++;
        printf("buffer full is is:- %d\n", buffer->full);
        printf("buffer empty is is:- %d\n", buffer->empty);

      }
      pthread_mutex_unlock(&lock);
   }
}



int main(){
        struct BUFF buffer;
        buffer.full = 0;
        buffer.empty = 5;
     
     pthread_t producer,consumer;
      pthread_mutex_init(&lock,NULL);
      
      pthread_create(&producer,NULL,th2,&buffer);
      pthread_create(&consumer,NULL,th1,&buffer);
      
      pthread_join(producer,NULL);
      pthread_join(consumer,NULL);

      return 0;
}

