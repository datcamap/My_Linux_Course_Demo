#ifndef HISTORY_LOGGER_H
#define HISTORY_LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TASK_DESCRIPTION_LENGTH_MAX 50     
#define LOG_ENTRY_LENGTH_MAX        100

typedef struct QueueList QueueList_t;

typedef struct TaskNode {
    char task_description[TASK_DESCRIPTION_LENGTH_MAX];
    struct TaskNode* next;
} TaskNode_t;

struct QueueList {
    TaskNode_t* head_of_queue;
    void (*add_task)(QueueList_t* ,const char*);
    TaskNode_t* (*get_next_task)(QueueList_t*);
    void (*print_task)(QueueList_t*);
    void (*delete)(QueueList_t*);
};

typedef struct HistoryList HistoryList_t;

typedef struct HistoryNode {
    char log_entry[LOG_ENTRY_LENGTH_MAX];
    struct HistoryNode* next;
    struct HistoryNode* prev;
} HistoryNode_t;

struct HistoryList {
    HistoryNode_t* history_cursor;
    void (*log_activity)(HistoryList_t*, const char*);
    void (*navigate)(HistoryList_t*);
    void (*delete)(HistoryList_t*);
};

QueueList_t queue_create(void);

HistoryList_t history_create(void);

#endif // HISTORY_LOGGER_H
