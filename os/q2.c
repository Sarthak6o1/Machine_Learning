#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>

void assignment01() {
    int a, b;
    printf("Assignment 01 (Process %d): Enter two integers: ", getpid());
    scanf("%d %d", &a, &b);
    printf("Assignment 01 (Process %d): Sum = %d\n", getpid(), a + b);
}
void createLadder(int level,int maxLevels){
      printf("Process Id: %d  Parent Id: %d\n",getpid(), getppid());
      if(level<maxLevels){
        pid_t pid=fork();{

        }
      if(pid==0){
        createLadder(level+1,maxLevels);
        exit(0);
      }
      else{
        wait(NULL);
      }
      }
      else{
        assignment01();
      }
}
int main(){
     int maxLevels =4;
     createLadder(1,maxLevels);
}