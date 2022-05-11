#include "stack.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const int INITIAL_CAPACITY = 1024;


int stackInit(IntStack *self) {
	self->stack = (int *)malloc(INITIAL_CAPACITY*sizeof(int));
	if(!self->stack) {
		fprintf(stderr, "Out of memory in stackInit.\n");
		return 1;
	}
	self->position = -1;
	self->capacity = INITIAL_CAPACITY;
	return 0;
}

void stackRelease(IntStack *self) {
	self->capacity = 0;
	free(self->stack);
}

void stackPush(IntStack *self, int i) {
	self->position++;
	if(self->position == self->capacity) {
		int newCapacity = 2*self->capacity;
		self->stack = realloc(self->stack, newCapacity*sizeof(int));
		if(!self->stack) {
			fprintf(stderr, "Out of memory in stackPush.\n");
			exit(-1);
		}
		self->capacity = newCapacity;
	}
	self->stack[self->position] = i;
}

int stackTop(const IntStack *self) {
	return self->stack[self->position];
}

int stackPop(IntStack *self) {
	if(self->position < 0) {
		fprintf(stderr, "Error: Tried to pop from empty stack.\n");
		exit(-1);
	}
	int out = self->stack[self->position];
	self->position--;
	return out;
}

int stackIsEmpty(const IntStack *self) {
	return self->position < 0;
}

void stackPrint(const IntStack *self) {
	for(int i = self->position; i >= 0; i--) {
		printf("%d\n", self->stack[i]);
	}
}