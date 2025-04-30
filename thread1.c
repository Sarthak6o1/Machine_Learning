#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
struct thread{
      int d1;
      int d2;
};
void* add_numbers(void* t){
    struct thread * t2= (struct  thread*)t;
    int sum=t2->d1+t2->d2;
    printf("The sum is = %d",sum);
} 
void* mul_numbers(void* t){
     struct thread * t1= (struct thread*)t;
     int mul=t1->d1*t1->d2;
     printf("The multiplication is = %d",mul);

    }
int main(){
    pthread_t add_thread,mul_thread;
    struct thread t;
    printf("Enter two Integers \n");
    scanf("%d",&t.d1);
    scanf("%d",&t.d2); 
    
    pthread_create(&add_thread,NULL,add_numbers,(void*)&t);
    pthread_create(&mul_thread,NULL,mul_numbers,(void*)&t);

    pthread_join(add_thread,NULL);
    pthread_join(mul_thread,NULL);

    printf("Both threads have completed execution\n");

    return 0;
}