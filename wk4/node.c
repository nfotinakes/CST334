// Name: Nicholas Fotinakes
// Date: 2022-03-29
// Title: Lab4 - node.c
// Description: This is the provided node.c used to implement a queue for Lab 4 FIFO simulation


#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct node* createNode(int data){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int getNodeData(struct node* n){
    return n->data;
}

struct node* getNodeNext(struct node* n){
    return n->next;
}

void destroyNode(struct node* n){
    free(n);
}
