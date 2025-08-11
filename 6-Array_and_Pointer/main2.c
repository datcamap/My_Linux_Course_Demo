#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include "history_logger.h"

#define PROCESSING_PERIOD 10

size_t procesing_time_stamp;

void process_tasks(QueueList_t*, HistoryList_t*);
void process_input(QueueList_t*, HistoryList_t*);

int main()
{
    procesing_time_stamp = time(NULL);

    QueueList_t _Queue_ = queue_create();
    HistoryList_t hislery_list = history_create();
    _Queue_.add_task(&_Queue_, "Initialize system");
    printf("[Task Queue Manager]\n \
            \t-a: add task\n \
            \t-t: print task queue\n \
            \t-h: history navigator\n \
            \t-d: delete task queue\n");
    while (1)
    {
        if (time(NULL) - procesing_time_stamp >= PROCESSING_PERIOD) {
            procesing_time_stamp = time(NULL);
            process_tasks(&_Queue_, &hislery_list);
        }

        process_input(&_Queue_, &hislery_list);
    }
    
    _Queue_.print_task(&_Queue_);

    return 0;
}

void process_tasks(QueueList_t* q_list, HistoryList_t* hist_list)
{
    TaskNode_t* task = q_list->get_next_task(q_list);
    if (task == NULL) {
        printf("No task to process.\n");
    } else {
        printf("Complete processing task \"%s\".\n",task->task_description);
        hist_list->log_activity(hist_list, task->task_description);
        free(task);
    }
}

void process_input(QueueList_t* q_list, HistoryList_t* hist_list)
{
    char input_char;
    char dummy_char;
    while((dummy_char=getchar()) == '\n');
    input_char = dummy_char;
    while ( getchar() != '\n' );
    printf("input_char: [%c]\n", input_char);

    switch (input_char) {
        case 'a': {
            char task_input[TASK_DESCRIPTION_LENGTH_MAX];
            printf("Enter task description (%d characters max): ", TASK_DESCRIPTION_LENGTH_MAX);
            if (fgets(task_input, sizeof(task_input), stdin) == NULL) {
                printf("Failed to add that description!");
                break;
            }
            task_input[strcspn(task_input, "\n")] = '\0'; // Replace newline character
            if (task_input != NULL) {
                q_list->add_task(q_list, task_input);
                printf("Added task \"%s\" to the queue.\n", task_input);
            } else {
                printf("Nothing added.\n");
            }
            
            break;
        }
        case 't': {
            q_list->print_task(q_list);
            break;
        }
        case 'h': {
            hist_list->navigate(hist_list);
            break;
        }
        case 'd': {
            q_list->delete(q_list);
            printf("Removed all tasks in queue!\n");
            break;
        }
        case '\n': break;
        case '\0': break;
        default: {
            printf("[Invalid Input] (%c) Please type in one of these letters:\n \
                    \t-a: add task\n \
                    \t-t: print task queue\n \
                    \t-h: history navigator\n \
                    \t-d: delete task queue\n", input_char);
        }
    }
}
