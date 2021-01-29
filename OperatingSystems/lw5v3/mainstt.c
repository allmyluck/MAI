#include "deque.h"


void help() {
    printf("PushBack: Press a\n");
    printf("PopBack: Press d\n");
    printf("PushFront: Press t\n");
    printf("PopFront: press r\n");
    printf("PRINT: Press p\n");
    printf("HELP: Press h\n");
    printf("SIZE: Press l\n");
    printf("EXIT: Press e\n");
}


int main() {
    dblinkedlist *l = createdblinkedlist();
    char c;
    int a;
    help();
    while (true) {
        scanf("%c", &c);
        switch (c) {
            case 'a':
                printf("Your element\n");
                scanf("%d", &a);
                PushBack(l,a);    
            break;
            case 'd':
                PopBack(l);
            break;
            case 't':
                printf("Your element\n");
                scanf("%d", &a);
                PushFront(l,a); 
            break;
            case 'e':
                Delete_dblinkedlist(&l);
                return 0;
            break;
            case 'h':
                help();
            break;
            case 'p':
                Printdblinkedlist(l);
            break;
            case 'l':
                printf("size:%lu\n",l->size);
            break;
            case 'r':
                PopFront(l);
            break;
        }
    }
    return 0;
}
