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

/********************************/
/* Functions defition for queue */
/********************************/

/**
 * @brief Creates a new task with the given description and appends it to the end of the queue.
 *
 * @param [in] queue_list   Pointer to the QueueList_t where the task will be added.
 * @param [in] description  Null-terminated string describing the task to be added.
 *
 * @note If the queue is empty, the new task becomes the head of the queue.
 *       The task description is copied into the TaskNode_t buffer using snprintf().
 * @warning Passing a NULL pointer for queue_list or description will cause undefined behavior.
 *          This function allocates memory for the new task using malloc(); the allocated
 *          memory must be freed later (e.g., via queue_delete() or queue_get_next_task()) 
 *          to avoid memory leaks. If malloc() fails, the function does nothing.
 */
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

/**
 * @brief Retrieves and removes the first task from the queue.
 *
 * @param [in] queue_list  Pointer to the QueueList_t from which the task will be retrieved.
 *
 * @return Pointer to the TaskNode_t representing the first task in the queue,
 *         or NULL if the queue is empty.
 *
 * @note The returned TaskNode_t is detached from the queue but not freed. The caller
 *       is responsible for freeing it after use.
 * @warning Passing a NULL pointer for queue_list will cause undefined behavior.
 *          Ensure proper memory management for the returned task node to avoid leaks.
 */
static TaskNode_t* queue_get_next_task(QueueList_t* queue_list)
{
    if (queue_list == NULL || queue_list->head_of_queue == NULL) {
        return NULL;
    }

    TaskNode_t* next_task = queue_list->head_of_queue;
    queue_list->head_of_queue = queue_list->head_of_queue->next;
    return next_task;
}

/**
 * @brief Prints all tasks currently stored in the queue.
 *
 * @param [in] queue_list  Pointer to the QueueList_t whose tasks will be printed.
 *
 * @note If the queue is empty (head_of_queue is NULL), a message indicating an empty queue
 *       is printed instead. Each task's description is printed on a separate line, prefixed
 *       with a hyphen.
 * @warning Passing a NULL pointer for queue_list will cause undefined behavior.
 *          Ensure that task_description in each TaskNode_t is a valid null-terminated string.
 */
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

/**
 * @brief Deletes all tasks in the given queue and resets the queue head pointer.
 *
 * @param [in] queue_list  Pointer to the QueueList_t whose tasks will be deleted.
 *
 * @note Calls task_delete() to recursively free all TaskNode_t elements starting
 *       from head_of_queue, then sets head_of_queue to NULL to avoid dangling pointers.
 * @warning Passing a NULL pointer for queue_list will cause undefined behavior.
 *          Ensure that all dynamically allocated members inside TaskNode_t are freed
 *          within task_delete() to prevent memory leaks.
 */
static void queue_delete(QueueList_t* queue_list)
{
    if (queue_list != NULL || queue_list->head_of_queue == NULL) {
        return;
    }

    task_delete(queue_list->head_of_queue);
    printf("Queue task cleared.\n");
    queue_list->head_of_queue = NULL;
}

/**
 * @brief Recursively deletes all tasks from the given task node onward.
 *
 * @param [in] task  Pointer to the starting TaskNode_t to delete. This node and all subsequent
 *                   nodes linked via `next` will be freed.
 *
 * @note Uses recursion; very long task lists may risk stack overflow.
 * @warning Only frees the TaskNode_t structures themselves. If TaskNode_t contains dynamically
 *          allocated members, free them before calling this function to prevent memory leaks.
 *          Passing NULL simply returns without performing any action.
 */
static void task_delete(TaskNode_t* task)
{
    if (task == NULL) {
        return;
    }

    task_delete(task->next);
    free(task);
}

/**********************************/
/* Functions defition for history */
/**********************************/

/**
 * @brief Creates a new history entry with a timestamp and appends it to the history list.
 *
 * @param [in] hist   Pointer to the HistoryList_t structure where the entry will be stored.
 * @param [in] entry  Null-terminated string containing the log message to record.
 *
 * @note The log entry is prepended with a timestamp in the format "[YYYY-MM-DD HH:MM:SS]".
 *       If hist->history_cursor is NULL, the new entry becomes the first entry in the list.
 * @warning This function uses malloc() for allocating the new node; ensure history deletion
 *          functions are used to free memory when no longer needed.
 *          If memory allocation fails, the function prints an error and does not append an entry.
 */
static void history_log_activity(HistoryList_t* hist, const char* entry)
{
    HistoryNode_t* new_entry = (HistoryNode_t*)malloc(sizeof(HistoryNode_t));
    if (hist!= NULL && new_entry != NULL) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char buffer1[50];
        strftime(buffer1, sizeof(buffer1), "[%Y-%m-%d %H:%M:%S]", t);
        snprintf(new_entry->log_entry, sizeof(new_entry->log_entry), "%s - %s", buffer1, entry);
        new_entry->next = NULL;
        new_entry->prev = NULL;

        if (hist->history_cursor == NULL) {
            hist->history_cursor = new_entry;
        } else {
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

/**
 * @brief Starts an interactive loop for navigating and managing the history list.
 *
 * @param [in] hist  Pointer to the HistoryList_t structure to navigate. Must have a valid
 *                   history_cursor to begin navigation.
 *
 * @note Displays a menu of available commands and repeatedly calls process_command()
 *       until the user issues the 'q' (quit) command.
 * @warning Passing a NULL pointer for hist or having hist->history_cursor set to NULL
 *          will skip navigation. Deleting the history during navigation will invalidate
 *          the current history_cursor pointer.
 */
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

/**
 * @brief Processes a single user command for navigating or modifying the history list.
 *
 * @param [in] hist  Pointer to the HistoryList_t structure to operate on. The function may
 *                   update hist->history_cursor or delete the history list based on the command.
 *
 * @return The command character entered by the user after processing.
 *
 * @note Supported commands:
 *       - 'n': Move to the next history entry.
 *       - 'p': Move to the previous history entry.
 *       - 'q': Quit navigation.
 *       - 'd': Delete the entire history list (requires 'y' confirmation).
 * @warning Passing a NULL pointer for hist will cause undefined behavior.
 *          Deleting the history list will free all nodes; ensure no other code references
 *          the deleted data after calling this function.
 */
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

/**
 * @brief Deletes an entire history list and frees all associated nodes.
 *
 * @param [in] hist  Pointer to the HistoryList_t to delete. The list's cursor and
 *                   all nodes before and after it will be freed.
 *
 * @note This function sets hist->history_cursor to NULL after deletion to avoid dangling pointers.
 * @warning Passing a pointer to an uninitialized or already freed HistoryList_t will cause
 *          undefined behavior. Ensure that all dynamically allocated members within each node
 *          are freed before calling this function.
 */
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

/**
 * @brief Recursively deletes all nodes in a doubly linked list from the given node forward.
 *
 * @param [in]  node  Pointer to the current HistoryNode_t to delete.
 *
 * @note The function uses recursion and may cause a stack overflow if the list is extremely long.
 * @warning This function only frees the node memory. If HistoryNode_t contains dynamically allocated
 *          members, free them before calling this function to avoid memory leaks.
 */
static void forward_node_delete(HistoryNode_t* node)
{
    if (node == NULL) {
        return;
    }

    forward_node_delete(node->next);
    free(node);
}

/**
 * @brief Recursively deletes all nodes in a doubly linked list from the given node backward.
 *
 * @param [in]  node  Pointer to the current HistoryNode_t to delete.
 *
 * @note The function uses recursion and may cause a stack overflow if the list is extremely long.
 * @warning This function only frees the node memory. If HistoryNode_t contains dynamically allocated
 *          members, free them before calling this function to avoid memory leaks.
 */
static void backward_node_delete(HistoryNode_t* node)
{
    if (node == NULL) {
        return;
    }

    backward_node_delete(node->prev);
    free(node);
}
