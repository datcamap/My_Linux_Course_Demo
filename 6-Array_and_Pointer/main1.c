#include <stdio.h>
#include <stdlib.h>

typedef struct TaskNode {
    char task_description[50];
    struct TaskNode* next;
} TaskNode_t;

static TaskNode_t* head_of_queue = NULL;

void queue_add_task(const char* description);
TaskNode_t* queue_get_next_task(void);
void print_task_queue(void);

int main() {
    queue_add_task("Initialize system");
    queue_add_task("Read sensor data");
    queue_add_task("Control pump");
    print_task_queue();
    
    TaskNode_t* task = queue_get_next_task();
    if (task != NULL) {
        printf("Processing: %s\n", task->task_description);
        free(task);
    }
    print_task_queue();
    
    queue_add_task("Sending notification");
    queue_add_task("Read sensor data again");
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
        } else {
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