#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>

#define PROCESSING_PERIOD 10 // seconds

typedef struct TaskNode {
    char task_description[50];
    struct TaskNode* next;
} TaskNode_t;

typedef struct HistoryNode {
    char log_entry[100];
    struct HistoryNode* next;
    struct HistoryNode* prev;
} HistoryNode_t;

static TaskNode_t* head_of_queue = NULL;
static HistoryNode_t* history_cursor = NULL;
size_t procesing_time_stamp;

int kbhit(void) {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void queue_add_task(const char* description);
TaskNode_t* queue_get_next_task(void);
void print_task_queue(void);
void history_log_activity(const char* entry);
void history_navigate(void);

int main() {
    procesing_time_stamp = time(NULL);
    queue_add_task("Initialize system");
    printf("[Task Queue Manager]\n\t-a: add task\n\t-h: history navigator\n\t-t: print task queue\n");
    while (1)
    {
        if (time(NULL) - procesing_time_stamp >= PROCESSING_PERIOD) {
            procesing_time_stamp = time(NULL);
            TaskNode_t* task = queue_get_next_task();
            if (task != NULL) {
                history_log_activity(task->task_description);
                free(task);
            }
        }
        
        if (kbhit() != 0) {
            char input = getchar();
            getchar(); // Consume the newline character
            if (input == 'h') {
                history_navigate();
            }
            else if (input == 'a') {
                char task_input[50];
                printf("Enter task description: ");
                fgets(task_input, sizeof(task_input), stdin);
                task_input[strcspn(task_input, "\n")] = '\0'; // Remove newline character
                queue_add_task(task_input);
            }
            else if (input == 't') {
                print_task_queue();
            }
            else {
                printf("Invalid input.\n\t-a: add task\n\t-h: history navigator\n\t-t: print task queue\n");
            }
        }
    }
    
    print_task_queue();

    return 0;
}

void queue_add_task(const char* description)
{
    TaskNode_t* new_task = (TaskNode_t*)malloc(sizeof(TaskNode_t));
    if (new_task != NULL) {
        snprintf(new_task->task_description, sizeof(new_task->task_description), "%s", description);
        new_task->next = NULL;

        if (head_of_queue == NULL) {
            head_of_queue = new_task;
        }
        else {
            TaskNode_t* current = head_of_queue;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_task;
        }
    } else {
        printf("Memory allocation failed for new task.\n");
    }
}

TaskNode_t* queue_get_next_task(void)
{
    if (head_of_queue == NULL) {
        printf("No tasks in the queue.\n");
        return NULL;
    }

    TaskNode_t* next_task = head_of_queue;
    head_of_queue = head_of_queue->next;
    return next_task;
}

void print_task_queue(void)
{
    if (head_of_queue == NULL) {
        printf("Task queue is empty.\n");
        return;
    }

    TaskNode_t* current = head_of_queue;
    printf("Current Task Queue:\n");
    while (current != NULL) {
        printf("- %s\n", current->task_description);
        current = current->next;
    }
}

void history_log_activity(const char* entry)
{
    HistoryNode_t* new_entry = (HistoryNode_t*)malloc(sizeof(HistoryNode_t));
    if (new_entry != NULL) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char buffer1[50];
        strftime(buffer1, sizeof(buffer1), "[%Y-%m-%d %H:%M:%S]", t);
        snprintf(new_entry->log_entry, sizeof(new_entry->log_entry), "%s - %s", buffer1, entry);
        new_entry->next = NULL;
        new_entry->prev = NULL;

        if (history_cursor == NULL) {
            history_cursor = new_entry;
        }
        else {
            HistoryNode_t* current = history_cursor;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_entry;
            new_entry->prev = current;
        }
    } else {
        printf("Memory allocation failed for history log.\n");
    }
}

void history_navigate(void)
{
    if (history_cursor == NULL) {
        printf("No history entries available.\n");
        return;
    }

    printf("[History Navigator]\n\t-n: next entry\n\t-p: previous entry\n\t-q: quit navigation\n");
    while (1) {
        if (kbhit() != 0) {
            char command = getchar();
            getchar();
            if (command == 'n') {
                if (history_cursor->next != NULL) {
                    history_cursor = history_cursor->next;
                }
                else {
                    printf("Reached bottom of history.\n");
                }
                printf(">>> %s <<<\n", history_cursor->log_entry);
            }
            else if (command == 'p') {
                if (history_cursor->prev != NULL) {
                    history_cursor = history_cursor->prev;
                }
                else {
                    printf("Reached top of history.\n");
                }
                printf(">>> %s <<<\n", history_cursor->log_entry);
            }
            else if (command == 'q') {
                printf("Exiting history navigation...\n");
                break;
            }
            else {
                printf("Invalid command.\n\t-n: next entry\n\t-p: previous entry\n\t-q: quit navigation\n");
            }
        }
    }
}