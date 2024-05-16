#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
} Process;

int findShortestJob(int n, Process p[], int time) {
    int min_index = -1;
    int min_bt = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && p[i].rt < min_bt && p[i].rt > 0) {
            min_bt = p[i].rt;
            min_index = i;
        }
    }
    return min_index;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].pid = i + 1;
        p[i].rt = p[i].bt;
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
    }

    int time = 0;
    int completed = 0;
    int current_process = -1;
    int seq[n];

    while (completed < n) {
        int shortest_job = findShortestJob(n, p, time);
        if (shortest_job != -1 && shortest_job != current_process) {
            if (current_process != -1 && p[current_process].rt > 0) {
                p[current_process].wt++;
            }
            seq[completed] = shortest_job;
            current_process = shortest_job;
        }

        if (current_process != -1) {
            p[current_process].rt--;
            time++;
            if (p[current_process].rt == 0) {
                p[current_process].ct = time;
                p[current_process].tat = p[current_process].ct - p[current_process].at;
                p[current_process].wt = p[current_process].tat - p[current_process].bt;
                completed++;
                current_process = -1;
            }
        } else {
            time++;
        }
    }

    float avgTAT = 0;
    float avgWT = 0;

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        avgTAT += p[i].tat;
        avgWT += p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    avgTAT /= n;
    avgWT /= n;

    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", seq[i] + 1);
    }
    printf("|\n");

    printf("Average TAT: %.2f\n", avgTAT);
    printf("Average WT: %.2f\n", avgWT);

    return 0;
}
