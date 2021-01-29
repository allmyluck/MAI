#ifndef DEQUE_H_
#define DEQUE_H_
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "dlfcn.h"

typedef int data_type;

typedef struct Node {
    data_type value;
    struct Node *next;
    struct Node *prev;
} Node;


typedef struct {
    size_t size;
    Node *head;
    Node *tail;
} dblinkedlist;

dblinkedlist* createdblinkedlist();
void Delete_dblinkedlist(dblinkedlist **l);
Node* PopFront(dblinkedlist *l);
Node* PopBack(dblinkedlist *l);
void PushFront(dblinkedlist *l,int data);
void PushBack(dblinkedlist *l,int value);
void Printdblinkedlist(dblinkedlist *list);

#endif 