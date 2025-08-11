#include "history_logger.h"

static void queue_add_task(QueueList_t* queue_list, const char* description);
static TaskNode_t* queue_get_next_task(QueueList_t* queue_list);
static void queue_print_task(QueueList_t* queue_list);
static void queue_delete(QueueList_t* queue_list);
static void task_delete(TaskNode_t* task);

static void history_log_activity(HistoryList_t* hist, const char* entry);
static void history_navigate(HistoryList_t* hist);
static char process_command(HistoryList_t* hist);
static void history_delete(HistoryList_t* hist);
static void forward_node_delete(HistoryNode_t* node);
static void backward_node_delete(HistoryNode_t* node);

QueueList_t queue_create(void)
{
    QueueList_t q_list;

    q_list.head_of_queue = NULL;
    q_list.add_task = queue_add_task;
    q_list.get_next_task = queue_get_next_task;
    q_list.print_task = queue_print_task;
    q_list.delete = queue_delete;

    return q_list;
}

HistoryList_t history_create(void)
{
    HistoryList_t hist_list;

    hist_list.history_cursor = NULL;
    hist_list.log_activity = history_log_activity;
    hist_list.navigate = history_navigate;
    hist_list.delete = history_delete;

    return hist_list;
}

/* Functions defition for queue*/
static void queue_add_task(QueueList_t* queue_list, const char* description)
{
    TaskNode_t* new_task = (TaskNode_t*)malloc(sizeof(TaskNode_t));
    if (new_task != NULL) {
        snprintf(new_task->task_description, sizeof(new_task->task_description), "%s", description);
        new_task->next = NULL;

        if (queue_list->head_of_queue == NULL) {
            queue_list->head_of_queue = new_task;
        }
        else {
            TaskNode_t* current = queue_list->head_of_queue;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_task;
        }
    } else {
        return;
    }
}

static TaskNode_t* queue_get_next_task(QueueList_t* queue_list)
{
    if (queue_list->head_of_queue == NULL) {
        return NULL;
    }

    TaskNode_t* next_task = queue_list->head_of_queue;
    queue_list->head_of_queue = queue_list->head_of_queue->next;
    return next_task;
}

static void queue_print_task(QueueList_t* queue_list)
{
    if (queue_list->head_of_queue == NULL) {
        printf("Task queue is empty.\n");
        return;
    }

    TaskNode_t* current = queue_list->head_of_queue;
    printf("Current Task Queue:\n");
    while (current != NULL) {
        printf("- %s\n", current->task_description);
        current = current->next;
    }
}

static void queue_delete(QueueList_t* queue_list)
{
    if (queue_list->head_of_queue == NULL) {
        return;
    }

    task_delete(queue_list->head_of_queue);
    queue_list->head_of_queue = NULL;
}

static void task_delete(TaskNode_t* task)
{
    if (task == NULL) {
        return;
    }

    task_delete(task->next);
    free(task);
}

/* Functions defition for history*/
static void history_log_activity(HistoryList_t* hist, const char* entry)
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

        if (hist->history_cursor == NULL) {
            hist->history_cursor = new_entry;
        }
        else {
            HistoryNode_t* current = hist->history_cursor;
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

static void history_navigate(HistoryList_t* hist)
{
    if (hist->history_cursor == NULL) {
        printf("No history entries available.\n");
        return;
    }

    printf("[History Navigator]\n \
            \t-n: next entry\n \
            \t-p: previous entry\n \
            \t-q: quit navigation\n \
            \t-d: delete history\n");
    while (process_command(hist) != 'q');

    printf("Exit history navigation.\n");
}

static char process_command(HistoryList_t* hist)
{
    char command;
    char dummy_char;
    while((dummy_char=getchar()) == '\n');
    command = dummy_char;
    while ( getchar() != '\n' );
    printf("command: [%c]\n", command);

    switch (command) {
        case 'n': {
            if (hist->history_cursor->next != NULL) {
                hist->history_cursor = hist->history_cursor->next;
            }
            else {
                printf("Reached bottom of history.\n");
            }
            printf(">>> %s <<<\n", hist->history_cursor->log_entry);

            break;
        }
        case 'p': {
            if (hist->history_cursor->prev != NULL) {
                hist->history_cursor = hist->history_cursor->prev;
            }
            else {
                printf("Reached top of history.\n");
            }
            printf(">>> %s <<<\n", hist->history_cursor->log_entry);
            break;
        }
        case 'q': {
            break;
        }
        case 'd': {
            printf("Are you sure you want to delete history? Type (y) to confirm. ");
            command = getchar();
            for (char i = getchar(); i != '\n' && i != EOF; );
            if (command == 'y') {
                hist->delete(hist);
                printf("Task history cleared!\n");
                command = 'q';
            }

            break;
        }
        default: {
            printf("[Invalid Command] Plese type in one of these letter:\n \
                    \t-n: next entry\n \
                    \t-p: previous entry\n \
                    \t-q: quit navigation\n \
                    \t-d: delete history\n");
        }
    }

    return command;
}

static void history_delete(HistoryList_t* hist)
{
    if (hist == NULL) {
        return;
    }

    forward_node_delete(hist->history_cursor->next);
    backward_node_delete(hist->history_cursor->prev);
    free(hist->history_cursor);
    hist->history_cursor = NULL;
}

static void forward_node_delete(HistoryNode_t* node)
{
    if (node == NULL) {
        return;
    }

    forward_node_delete(node->next);
    free(node);
}

static void backward_node_delete(HistoryNode_t* node)
{
    if (node == NULL) {
        return;
    }

    backward_node_delete(node->prev);
    free(node);
}
