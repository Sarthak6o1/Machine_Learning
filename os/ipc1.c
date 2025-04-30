#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

#define msg 100

int main(){
      pid_t pid;
      int pipe1[2];
      int pipe2[2];
       
      char buffer[msg];
      char parent_msg [msg]="Hi from Parent";
      char child_msg [msg]="Hello from child";

      if(pipe(pipe1)==-1 || pipe(pipe2)==-1){
        perror("Pipe failed\n");
        exit(0);
      }
     
      pid=fork();
      if(pid>0){
        close(pipe1[0]);
        close(pipe2[1]);
        
        write(pipe1[1],parent_msg,strlen(parent_msg)+1);
        read(pipe2[0],buffer,msg);
        printf("Parent id %d received %s\n",getpid(),buffer);
      
        close(pipe1[1]);
        close(pipe2[0]);
      } 
       else{
             close(pipe1[1]);
             close(pipe2[0]);

             read(pipe1[0],buffer,msg);
             printf("Child id %d received %s\n",getpid(),buffer);
             write(pipe2[1],child_msg,strlen(child_msg)+1);
        }
        
        close(pipe1[0]);
        close(pipe2[1]);

      
       return 0;
}