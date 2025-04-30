#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

// Function to add two integers
void add_two_numbers() {
    int a, b;
    printf("Enter two integers to add: ");
    scanf("%d %d", &a, &b);
    printf("Sum by process %d: %d\n", getpid(), a + b);
}

// Function to print contents of a file
void print_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("File open error");
        return;
    }
    
    char buf[1024];
    int n;
    printf("Contents of %s:\n", filename);
    while ((n = read(fd, buf, sizeof(buf)-1)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
    }
    printf("\n");
    close(fd);
}

int main() {
    pid_t c1, c2;
    int status;

    // Create first child process
    c1 = fork();
    
    if (c1 == 0) {
        // First child: add two integers
        add_two_numbers();
        exit(0);
    } else if (c1 > 0) {
        // Create second child process
        c2 = fork();
        
        if (c2 == 0) {
            // Second child: print file contents
            print_file("file1.txt");
            print_file("file2.txt");
            exit(0);
        } else if (c2 > 0) {
            // Parent process: wait for both children
            waitpid(c1, &status, 0);
            waitpid(c2, &status, 0);
            
            // After both children complete, parent does addition
            add_two_numbers();
        } else {
            perror("Second fork failed");
            exit(1);
        }
    } else {
        perror("First fork failed");
        exit(1);
    }
    
    return 0;
}
