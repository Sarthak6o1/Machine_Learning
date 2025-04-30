#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include <string.h>
#define msg 100
int main(){
       int pipe1[2];
       int pipe2[2];
       pid_t pid;
       char parent_msg[msg]="Hi from Parent";
       char child_msg[msg]="Hello from Child";
       char buffer[msg];

       if(pipe(pipe1)==-1 || pipe(pipe2)==-1){
        perror("Pipe Creation Field");
        exit(1);
       }
       pid=fork();
       if(pid<0){
         perror("Fork Failed");
         exit(1);
       }
       if(pid>0){
        close(pipe1[0]);
        close(pipe2[1]);

        for(int i=0;i<5;i++){
             write(pipe1[1],parent_msg,strlen(parent_msg)+1);

             read(pipe2[0],buffer,msg);
             printf("Parent (PId:%d) received: %s \n",getpid(),buffer);
        }
        close(pipe1[1]);
             close(pipe2[0]);
       }
       else{
        close(pipe1[1]); // Close writing end of pipe1
        close(pipe2[0]); // Close reading end of pipe2

        for (int i = 0; i < 5; i++) {
            // Read message from parent
            read(pipe1[0], buffer, msg);
            printf("Child (PID: %d) received: %s\n", getpid(), buffer);
            // Send message to parent
            write(pipe2[1], child_msg, strlen(child_msg) + 1);
        }

        close(pipe1[0]);
        close(pipe2[1]);
       }
     return 0;

}