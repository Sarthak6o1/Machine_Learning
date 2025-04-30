#include <stdio.h>

#define MAX_PROCESSES 5

// Structure for Process
typedef struct {
    char id[3]; // Process ID (e.g., P1, P2)
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

// Function to implement FCFS Scheduling
void fcfs_scheduling(Process processes[], int n) {
    int total_tat = 0, total_wt = 0;
    
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
        if (processes[i].completion_time < processes[i].arrival_time)
            processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
    }

    // Calculate Turnaround Time & Waiting Time
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
    }

    printf("\nFCFS Scheduling:\n");
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

// Function to implement Round Robin Scheduling
void round_robin_scheduling(Process processes[], int n, int quantum) {
    int remaining_time[MAX_PROCESSES], total_tat = 0, total_wt = 0;
    int time = 0, completed = 0;
    
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && processes[i].arrival_time <= time) {
                executed = 1;
                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    remaining_time[i] = 0;
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    total_tat += processes[i].turnaround_time;
                    total_wt += processes[i].waiting_time;
                    completed++;
                }
            }
        }
        if (!executed) time++; // Move time forward if no process is executed
    }

    printf("\nRound Robin Scheduling (Time Quantum = %d):\n", quantum);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

// Main function
int main() {
    Process processes[MAX_PROCESSES] = {
        {"P1", 0, 4},
        {"P2", 1, 3},
        {"P3", 2, 1},
        {"P4", 3, 2},
        {"P5", 4, 5}
    };

    fcfs_scheduling(processes, MAX_PROCESSES);
    round_robin_scheduling(processes, MAX_PROCESSES, 2);

    return 0;
}
