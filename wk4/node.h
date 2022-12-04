// Name: Nicholas Fotinakes
// Date: 2022-03-29
// Title: Lab4 - node.h
// Description: This is the provided node.h used to implement a queue for Lab 4


#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node* next;
};

struct node* createNode(int data);
int getNodeData(struct node* n);
struct node* getNodeNext(struct node* n);
void destroyNode(struct node* n);

#endif // NODE_H //
