#include "syntree.h"

#include <stdio.h>
#include <stdlib.h>

const int INITIAL_CAPACITY = 1024;

#define TYPE_NUMBER 0
#define TYPE_CHILDREN_LIST 1

int syntreeInit(Syntree *self) {
	self->len = 0;
	self->memory = (SyntreeNode *)malloc(INITIAL_CAPACITY*sizeof(SyntreeNode));
	if(!self->memory) {
		fprintf(stderr, "Out of memory in stackPush.\n");
		exit(-1);
	}
	self->capacity = INITIAL_CAPACITY;
	return 0;
}

void syntreeRelease(Syntree *self) {
	for(int i = 0; i < self->len; i++) {
		switch(self->memory[i].type) {
			case TYPE_NUMBER:
				break;
			case TYPE_CHILDREN_LIST:
				free(self->memory[i].content.childrenList.children);
				break;
			default:
				fprintf(stderr, "Weird type %d. Someone changed the internal representation or undefined value.\n", self->memory[i].type);
		}
	}
	free(self->memory);
}

SyntreeNodeID createNode(Syntree *self) {
	self->len++;
	if (self->capacity == self->len) {
		int newCapacity = 2*self->capacity;
		self->memory = realloc(self->memory, newCapacity*sizeof(SyntreeNode));
		self->capacity = newCapacity;
		if (!self->memory) {
			fprintf(stderr, "Out of memory in syntreeNodeNumber.\n");
			exit(-1);
		}
	}
	return self->len - 1;
}

SyntreeNodeID syntreeNodeNumber(Syntree *self, int number) {
	int node = createNode(self);
	self->memory[node].type = TYPE_NUMBER;
	self->memory[node].content.value = number;
	return node;
}

SyntreeNodeID syntreeNodeTag(Syntree *self, SyntreeNodeID id) {
	SyntreeNodeID node = createNode(self);
	self->memory[node].type = TYPE_CHILDREN_LIST;
	self->memory[node].content.childrenList.len = 1;
	self->memory[node].content.childrenList.children = (SyntreeNodeID*)malloc(sizeof(SyntreeNodeID));
	if(!self->memory[node].content.childrenList.children) {
		fprintf(stderr, "Out of memory in syntreeNodeNumber.\n");
		exit(-1);
	}
	self->memory[node].content.childrenList.children[0] = id;
	return node;
}

SyntreeNodeID syntreeNodePair(Syntree *self, SyntreeNodeID id1, SyntreeNodeID id2) {
	SyntreeNodeID node = createNode(self);
	self->memory[node].type = TYPE_CHILDREN_LIST;
	self->memory[node].content.childrenList.len = 2;
	self->memory[node].content.childrenList.children = (SyntreeNodeID*)malloc(2*sizeof(SyntreeNodeID));
	if(!self->memory[node].content.childrenList.children) {
		fprintf(stderr, "Out of memory in syntreeNodeNumber.\n");
		exit(-1);
	}
	self->memory[node].content.childrenList.children[0] = id1;
	self->memory[node].content.childrenList.children[1] = id2;
	return node;
}

SyntreeNodeID syntreeNodeAppend(Syntree *self, SyntreeNodeID list, SyntreeNodeID elem) {
	self->memory[list].content.childrenList.len++;
	self->memory[list].content.childrenList.children = (SyntreeNodeID *)realloc(
		self->memory[list].content.childrenList.children,
		self->memory[list].content.childrenList.len*sizeof(SyntreeNodeID)
	);
	if (!self->memory[list].content.childrenList.children) {
		fprintf(stderr, "Out of memory in syntreeNodeNumber.\n");
		exit(-1);
	}
	self->memory[list].content.childrenList.children[self->memory[list].content.childrenList.len - 1] = elem;
	return list;
}

SyntreeNodeID syntreeNodePrepend(Syntree *self, SyntreeNodeID elem, SyntreeNodeID list) {
	self->memory[list].content.childrenList.len++;
	self->memory[list].content.childrenList.children = (SyntreeNodeID *)realloc(
		self->memory[list].content.childrenList.children,
		self->memory[list].content.childrenList.len*sizeof(SyntreeNodeID)
	);
	if (!self->memory[list].content.childrenList.children) {
		fprintf(stderr, "Out of memory in syntreeNodeNumber.\n");
		exit(-1);
	}
	for(int i = 0; i < self->memory[list].content.childrenList.len; i++) {
		SyntreeNodeID old = self->memory[list].content.childrenList.children[i];
		self->memory[list].content.childrenList.children[i] = elem;
		elem = old;
	}
	return list;
}

int depth = 0; //UGLY AF! TODO: fix
void printTabs() {
	for(int i = 0; i < depth; i++) {
		printf("\t");
	}
}
void syntreePrint(const Syntree *self, SyntreeNodeID root) {
	switch(self->memory[root].type) {
		case TYPE_NUMBER:
			printTabs();
			printf("(%d)\n", self->memory[root].content.value);
			break;
		case TYPE_CHILDREN_LIST:
			printTabs();
			printf("{\n");
			depth++;
			for (int i = 0; i < self->memory[root].content.childrenList.len; i++) {
				syntreePrint(self, self->memory[root].content.childrenList.children[i]);
			}
			depth--;
			printTabs();
			printf("}\n");
			break;
		default:
			fprintf(stderr, "Weird type %d. Someone changed the internal representation or undefined value.\n", self->memory[root].type);
	}   
}