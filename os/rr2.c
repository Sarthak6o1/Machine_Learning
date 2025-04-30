#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 5
#define MAX_QUEUE     20

// Structure for Process
typedef struct {
    char id[3];            // Process ID (e.g., "P1")
    int arrival;           // Arrival time
    int burst;             // Burst time
    int completion;        // Completion time
    int turnaround;        // Turnaround time
    int waiting;           // Waiting time
} Process;

// Compare function for sorting by arrival time
int cmp_arrival(const void *a, const void *b) {
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    return p1->arrival - p2->arrival;
}

// Round Robin Scheduling using a proper ready queue
void rr_with_queue(Process P[], int n, int quantum) {
    int rem[MAX_PROCESSES];
    int queue[MAX_QUEUE], front = 0, rear = 0;
    int time = 0, completed = 0, idx = 0;
    int total_tat = 0, total_wt = 0;

    // Sort processes by arrival time
    qsort(P, n, sizeof(Process), cmp_arrival);

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        rem[i] = P[i].burst;
    }

    // Enqueue any processes that arrive at time 0
    while (idx < n && P[idx].arrival <= time) {
        queue[rear++] = idx++;
    }

    while (completed < n) {
        if (front == rear) {
            // No ready process → fast-forward time to next arrival
            time = P[idx].arrival;
            queue[rear++] = idx++;
            
        }

        int i = queue[front++];       // Dequeue index
        int dt = (rem[i] > quantum ? quantum : rem[i]);
        time += dt;
        rem[i] -= dt;

        // Enqueue newly arrived processes during this time slice
        while (idx < n && P[idx].arrival <= time) {
            queue[rear++] = idx++;
        }

        if (rem[i] > 0) {
            // Not finished → re-enqueue
            queue[rear++] = i;
        } else {
            // Finished → record metrics
            P[i].completion = time;
            P[i].turnaround = P[i].completion - P[i].arrival;
            P[i].waiting    = P[i].turnaround - P[i].burst;
            total_tat      += P[i].turnaround;
            total_wt       += P[i].waiting;
            completed++;
        }
    }

    // Print averages
    printf("\nProper Round Robin Scheduling (Time Quantum = %d):\n", quantum);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time:    %.2f\n", (float)total_wt  / n);
}

int main() {
    Process P[MAX_PROCESSES] = {
        {"P1", 0, 3},
        {"P2", 1, 2},
        {"P3", 2, 4},
        {"P4", 3, 5},
        {"P5", 4, 1}
    };

    rr_with_queue(P, MAX_PROCESSES, 2);
    return 0;
}
