#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
void addTwoNumbers() {
    int a, b;
    printf(" Enter two integers to add: \n");
    scanf("%d %d", &a, &b);
    printf("Process %d Sum = %d\n", getpid(), a + b);
}
void printfile(const char* filename) {
    char command[100];
    snprintf(command, sizeof(command), "cat %s", filename);
    system(command);
}

int main(){
     pid_t child1,child2;

     child1=fork();

     if(child1==0){
         addTwoNumbers();
         exit(0);
     }
     else {
         child2=fork();

          if(child2==0){
            printfile("file1.txt");
            printfile("file1.txt");
            exit(0);  
        }
        else{
            wait(NULL);
            wait(NULL);
            addTwoNumbers();
        }
     }
  return 0;
}