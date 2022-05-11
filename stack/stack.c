#include "stack.h"

#include <string.h>

const INITIAL_CAPACITY = 1024;


int stackInit(IntStack *self) {
    self->stackStart = (int *)malloc(INITIAL_CAPACITY);
	self->stackPointer = self->stackStart - 1;
	self->capacity = INITIAL_CAPACITY;
}

void stackRelease(IntStack *self) {
	self->capacity = 0;
	free(self->stackPointer);
}

void stackPush(IntStack *self, int i) {
    self->stackPointer++;
	if(self->stackPointer - self->stackStart == self->capacity) {
		int newCapacity = 2*self->capacity;
		int *biggerPointer = malloc(newCapacity);
		memcpy(biggerPointer, self->stackStart, self->capacity*sizeof(int));
		free(self->stackStart);
		self->stackStart = biggerPointer;
		self->stackPointer = self->stackStart + self->capacity;
		self->capacity = newCapacity;
	}
    int out = *self->stackPointer;
    return out;
}

int stackTop(const IntStack *self) {
    return *self->stackPointer;
}

int stackPop(IntStack *self) {
    int out = *self->stackPointer;
    self->stackPointer--;
    return out;
}

int stackIsEmpty(const IntStack *self) {
    return self->stackPointer < self->stackStart;
}

void stackPrint(const IntStack *self) {
    int* curr = self->stackPointer;
	while(curr >= self->stackStart) {
        printf("[%d] %d",curr,*curr);
        curr--;
    }
}