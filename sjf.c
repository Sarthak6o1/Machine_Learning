#include <stdio.h>

// Define a structure to store process information
struct process {
    int pId;
    int arrivalTime;
    int burstTime;
    int startTime;
    int completionTime;
    int TAT; // Turnaround time
    int WAT; // Waiting time
};

void sjf_nonpreemptive(struct process p[], int n) {
    // Sort by arrival time
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].arrivalTime > p[j+1].arrivalTime) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;

    for(int i = 0; i < n; i++) {
        int min_burst_index = i;

        for(int j = i; j < n; j++) {
            if(p[j].arrivalTime <= current_time && 
               p[j].burstTime < p[min_burst_index].burstTime) {
                min_burst_index = j;
            }
        }

        if(p[min_burst_index].arrivalTime > current_time) {
            current_time = p[min_burst_index].arrivalTime;
        }

        struct process temp = p[i];
        p[i] = p[min_burst_index];
        p[min_burst_index] = temp;

        p[i].startTime = current_time;
        p[i].completionTime = current_time + p[i].burstTime;
        p[i].TAT = p[i].completionTime - p[i].arrivalTime;
        p[i].WAT = p[i].TAT - p[i].burstTime;
        current_time = p[i].completionTime;
    }

    // Print output
    printf("\nProcess | Arrival | Burst | Start | Completion | TAT | WAT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t| %d\t| %d\t| %d\t| %d\t\t| %d\t| %d\n",
               p[i].pId, p[i].arrivalTime, p[i].burstTime,
               p[i].startTime, p[i].completionTime, p[i].TAT, p[i].WAT);
    }

    float avg_TAT = 0, avg_WAT = 0;
    for(int i = 0; i < n; i++) {
        avg_TAT += p[i].TAT;
        avg_WAT += p[i].WAT;
    }

    avg_TAT /= n;
    avg_WAT /= n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_TAT);
    printf("Average Waiting Time: %.2f\n", avg_WAT);
}

int main() {
    int n = 4;  // Hardcoded number of processes

    struct process processes[] = {
        {1, 0, 2},   // {pId, arrivalTime, burstTime}
        {2, 1, 4},
        {3, 2, 2},
        {4, 3, 1}
    };

    sjf_nonpreemptive(processes, n);

    return 0;
}
