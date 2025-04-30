#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

#define n 5

sem_t forks[n];
sem_t mutex;
 
void *phil(void *arg){
      int id=*(int*)arg;
      int left=id;
      int right=(id+1)%n;

      int k=5; 
    while(k--){
     printf("The philospher id :%d is Thinking \n",id+1 );  
     sleep(2); 
      sem_wait(&forks[left]);
      sem_wait(&forks[right]);
      sem_wait(&mutex);
      
      printf("The philospher id :%d is Eating \n",id+1);
      sem_post(&forks[left]);
      sem_post(&forks[right]);
      sem_post(&mutex);
    
    }


}
int main(){
     pthread_t philosphers[n];
     int ids[n];
     sem_init(&mutex,0,n-1);

     for(int i=0;i<n;i++){
         ids[i]=i;
         sem_init(&forks[i],0,1);
     }

     
     for(int i=0;i<n;i++){
      pthread_create(&philosphers[i],NULL,phil,&ids[i]);
     }
     for(int i=0;i<n;i++){
         pthread_join(philosphers[i],NULL);
     }

      return 0;
}