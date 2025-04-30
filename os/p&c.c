#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define max 20
#define buffer_size 5

sem_t mutex;
sem_t full;
sem_t empty;

int buffer[buffer_size];
int in=0;
int out=0;
int prod_cnt=0;
int cons_cnt=0;

void *produce(void * arg){
        
       int item=1;
       while(prod_cnt<max){
            sem_wait(&empty);
            sem_wait(&mutex);

            buffer[in]=item;
            printf("Produced the item %d",item);
            item++;
            in=(in+1)%buffer_size;
            prod_cnt++;
           
            sem_post(&full);
            sem_post(&mutex);
       
    }
}
void *consume(void * arg){
        while(cons_cnt<max){
             sem_wait(&full);
             sem_wait(&mutex);
             
             int item=buffer[out];
             printf("Consumed %d",item);
             out=(out+1)%buffer_size;
             cons_cnt++;

             sem_post(&empty);
             sem_post(&mutex);
             
            }

}
int main(){
     pthread_t producer,consumer;
     sem_init(&mutex,0,1);
     sem_init(&full,0,0);
     sem_init(&empty,0,buffer_size);
     
     pthread_create(&producer,NULL,produce,NULL);
     pthread_create(&consumer,NULL,consume,NULL);
     
     pthread_join(producer,NULL);
     pthread_join(consumer,NULL);
     
     return 0;
}
