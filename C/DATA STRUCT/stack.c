
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// recursive structure
typedef struct cell  {
	
	void* value;
	struct cell* next;

} CELL, * POINTER ;	// Different names for the same struct

typedef struct stack {

	POINTER top;
	int size;	// Number of elements contained in stack

} STACK;

typedef struct list_t {
	int entier;
	char msg[10];
}list_t;


// Create an empty sack
STACK* stack_create()
{
	STACK* s = (STACK*)malloc(sizeof(STACK));
	
	s -> size = 0;
	s -> top = NULL;

	return s;
}



int stack_pop(STACK* s, void** value)
{
	if(s->top )
	s->top = s->top->next;	// Top becomes the previous element
	s->size--;

	return s->size;

}

// Return 1 if sack is empty
int stack_is_empty(STACK *s)
{
	if (s->size) return 0;
	else return 1;
}



int stack_push(STACK* s, const void* value)
{
	CELL *c = (CELL *)malloc(sizeof(CELL));
	c->value = value;
	c->next = s->top;
	s->top = c;
	s -> size++;

	return s -> size;	// Return the new size of stack
}


int stack_delete(STACK *s)
{
	free(s);	//Freeing the memory
	return 1;
}

void* stack_top_value(STACK* s)
{
	return s->top->value;
}

int main()
{
	STACK* myStack = stack_create(), myStack2 = stack_create();

	printf("Is stack empty ? : %d\n", stack_is_empty(myStack));

	stack_push(myStack, 10);

	printf("Top value after push : %d\n", stack_top_value(myStack));
	stack_push(myStack, 100);
	printf("Top value after push : %d\n", stack_top_value(myStack));
	stack_pop(myStack, 0);
	printf("Top value after pop : %d\n", stack_top_value(myStack));

	printf("Is stack empty ? : %d\n", stack_is_empty(myStack));
	stack_delete(myStack);

	list_t list0 = { 1, "petit" };
	list_t list1 = { 2, "moyen" };

	stack_push(myStack2, list0);

}
 