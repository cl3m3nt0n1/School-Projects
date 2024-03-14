#include "queue.h"
#include <string.h>

// create an empty queue
QUEUE* queue_create ()
{
    QUEUE *q = malloc(sizeof(QUEUE));
    q->first = NULL;
    q->last = NULL;
    q->sizeQ = 0;
    return q;
}


// test if a QUEUE is empty
int queue_is_empty(QUEUE *q)
{

    return (q->first == NULL);
}

// add an element at the end of the QUEUE
int queue_enqueue (QUEUE *q, const void *value)
{

    POINTER newCell= malloc(sizeof(CELL));
    if(newCell == NULL)
        return 0;
    else
    {
        newCell->value = (void *)value;
        newCell->next = NULL;
        if(!queue_is_empty(q))
        {
            q->last->next = newCell;
        }
        else
        {
            q->first = newCell;
        }
        q->last = newCell;
        q->sizeQ++;
    }
    return 1;
}

int queue_dequeue(QUEUE *q, void **value)
{
    if(queue_is_empty(q))
        return 0;
    else
    {
        *value = q->first->value;
        POINTER tmp = q->first;
        q->first = q->first->next;
        if(q->first == NULL)
            q->last = NULL;
        free(tmp);
        q->sizeQ--;
    }
    return 1;
}


int queue_destroy(QUEUE *q)
{
    void *out_value;
    while(q->sizeQ > 0)
    {
        if(queue_dequeue(q, (void **)&out_value))
        {
            free(out_value);
        }
    }
    memset(q, 0, sizeof(QUEUE));
    return 1;
}

int queue_print_int(QUEUE *q)
{
    CELL *cour= q->first;
    int i;
    for (i=1; i<=queue_size(q); i++)
    {
        int x = (*((int *)(cour->value)));
        printf(" %3d : %d \n", i, x);
        cour = cour->next ;
    }
    return 1;
}

int queue_print_string(QUEUE *q)
{
    CELL *cour= q->first;
    int i;
    for (i=1; i<=queue_size(q); i++)
    {
        char *s = ((char *)(cour->value));
        printf(" %3d : %s \n", i, s);
        cour = cour->next ;
    }
    return 1;
}


void inverse_recur(QUEUE *q, void *value) {

    if (queue_size(q) >1) {
       void *value;
       queue_dequeue(q, &value);
       inverse_recur(q,value);
       queue_enqueue(q,value);
    }
}

int queue_shift(QUEUE* q) {

   void *value;
   queue_dequeue(q, &value);
   inverse_recur(q,value);
   queue_enqueue(q,value);
   return 1;

}


/** clone q1 dans q2
On fait l'hypothèse que q2 est déjà alloué (sinon pas possible il faudrait prendre un **)
*/
int queue_clone(QUEUE* q1, QUEUE* q2) {
    if (q1 == NULL || q2 == NULL)
        return 0;

   POINTER cour = q1->first;
   while (cour != NULL)
   {
        queue_enqueue(q2, cour->value);
        cour = cour->next;
    }

   return 1;
}


