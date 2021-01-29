#include "deque.h" 
 
 
dblinkedlist* createdblinkedlist() {
    dblinkedlist *tmp = (dblinkedlist*) malloc(sizeof(dblinkedlist));
    if (tmp == NULL) {
        free(tmp);
        exit(1);
    }
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}


void Delete_dblinkedlist(dblinkedlist **l) {
    Node *tmp = (*l)->head;
    Node *next = NULL;
    while(tmp) {
        next = tmp->next;
        free(tmp);
        tmp = NULL;
        tmp = next;
    }
    (*l)->size = 0;
    free(*l);
    (*l) = NULL;
 }


bool list_is_empty(dblinkedlist *l) {
    return l->size == 0;
}


void PushFront(dblinkedlist *l, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        Delete_dblinkedlist(&l);
        exit(1);
    }
    tmp->value = data;
    tmp->next = l->head;
    tmp->prev = NULL;
    if (l->head) {
        l->head->prev = tmp;
    }
    l->head = tmp;
 
    if (l->tail == NULL) {
        l->tail = tmp;
    }
    l->size++;
}


Node* PopBack(dblinkedlist *l) {
    if(l->tail == NULL) {
        return NULL;
    }
    if(l->size == 1) {
        free(l->tail);
        l->size--;
        l->head = NULL;
        l->tail = NULL;
        return NULL;
    }
    Node *tmp = l->tail->prev;
    free(l->tail);
    l->tail = NULL;
    tmp->next = NULL;
    l->tail = tmp;
    l->size--;
    return l->tail;
}


Node* PopFront(dblinkedlist *l) {
    if(l->head == NULL) {
        return NULL;
    }
    if(l->size == 1) {
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
        l->size--;
        return NULL;
    }
    Node* tmp = l->head->next;
    free(l->head);
    l->head = NULL;
    tmp->prev = NULL;
    l->head = tmp;
    l->size--;
    return l->head;
}


void PushBack(dblinkedlist *list, int value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        Delete_dblinkedlist(&list);
        exit(1);
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;
 
    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}


void Printdblinkedlist(dblinkedlist *list) {
    if(!list_is_empty(list)) {
        Node *tmp = list->head;
        printf("null");
        while (tmp) {
            printf(" <-> %d ", tmp->value);
            tmp = tmp->next;
        }
        printf(" <-> null");
        printf("\n");
    } else {
        printf("List is empty\n");
    }
}