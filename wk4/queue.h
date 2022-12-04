// Name: Nicholas Fotinakes
// Date: 2022-03-29
// Title: Lab4 - queue.h
// Description: This is the provided queue.h used to implement queue used in Lab 4 FIFO simulation


#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include "node.h"

struct queue {
  struct node* head;
  struct node* tail;
};

struct queue* queue_create();
struct node* enqueue(struct queue* q, int data);
void dequeue(struct queue* q);
int queue_length(struct queue* q);
void queue_traverse(struct queue* q);
void queue_destroy(struct queue* q);
struct node* queue_find(struct queue* q, int data);

#endif // QUEUE_H //
