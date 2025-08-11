#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TaskNode {
    char task_description[50];
    struct TaskNode* next;
} TaskNode_t;

typedef struct QueueList {
    TaskNode* head_of_queue;
} QueueList_t

typedef struct HistoryNode {
    char log_entry[100];
    struct HistoryNode* next;
    struct HistoryNode* prev;
} HistoryNode_t;

