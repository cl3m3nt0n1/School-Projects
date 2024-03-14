#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define queue_size(queue) ((queue)->sizeQ)


/* a cell of the queue */
typedef struct cell
{
    void *value;
    struct cell *next; // pointer on the next element
} CELL, * POINTER;

typedef struct _queue
{
    POINTER first; // pointer to the first CELL of the queue
    POINTER last; // pointer to the last CELL of the queue
    int sizeQ;
} QUEUE;

// create an empty stack
QUEUE* queue_create ();
// returns 1 if empty, 0 otherwise
int queue_is_empty(QUEUE *);
//Add an element at the back of the queue
int queue_enqueue(QUEUE *, const void *);
// remove the first cell of the queue and return its value
int queue_dequeue(QUEUE *q, void **value);
//destroy the queue
int queue_destroy(QUEUE *q);
// return the size of the queue

// TD Sur les files d'attente
int queue_print_int(QUEUE*);
int queue_print_string(QUEUE*);
int queue_shift(QUEUE*);
int queue_clone(QUEUE*, QUEUE*);
