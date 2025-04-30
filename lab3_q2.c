#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to represent assignment 01
void do_assignment_01() {
    printf("Process %d is executing Assignment 01\n", getpid());
    // Simulate some work for assignment 01
    sleep(1);
    printf("Assignment 01 completed\n");
}

int main() {
    pid_t pid, child_pid;
    int status;
    
    // Process 1 (original parent)
    printf("Process 1 - PID: %d, Parent PID: %d\n", getpid(), getppid());
    
    // Create Process 2
    pid = fork();
    
    if (pid < 0) {
        perror("Fork 1 failed");
        exit(1);
    } else if (pid == 0) {
        // Process 2 (child of Process 1)
        printf("Process 2 - PID: %d, Parent PID: %d\n", getpid(), getppid());
        
        // Create Process 3
        pid = fork();
        
        if (pid < 0) {
            perror("Fork 2 failed");
            exit(1);
        } else if (pid == 0) {
            // Process 3 (child of Process 2)
            printf("Process 3 - PID: %d, Parent PID: %d\n", getpid(), getppid());
            
            // Create Process 4
            pid = fork();
            
            if (pid < 0) {
                perror("Fork 3 failed");
                exit(1);
            } else if (pid == 0) {
                // Process 4 (child of Process 3, lowest in hierarchy)
                printf("Process 4 - PID: %d, Parent PID: %d\n", getpid(), getppid());
                
                // Process 4 executes assignment 01
                do_assignment_01();
                
                exit(0);  // Process 4 exits
            } else {
                // Process 3 waits for Process 4 to complete
                child_pid = wait(&status);
                printf("Process 3: Child process (PID: %d) has completed\n", child_pid);
                exit(0);  // Process 3 exits
            }
        } else {
            // Process 2 waits for Process 3 to complete
            child_pid = wait(&status);
            printf("Process 2: Child process (PID: %d) has completed\n", child_pid);
            exit(0);  // Process 2 exits
        }
    } else {
        // Process 1 waits for Process 2 to complete
        child_pid = wait(&status);
        printf("Process 1: Child process (PID: %d) has completed\n", child_pid);
    }
    
    return 0;
}
