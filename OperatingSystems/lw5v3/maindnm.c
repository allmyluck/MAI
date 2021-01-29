#include "deque.h"
#define Error_dlsym 5

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

void* get(void *libHandle, char* name) {
    void* temp = dlsym(libHandle, name);
    if(temp == NULL) {
        fprintf(stderr, "%s\n", dlerror());
        exit(Error_dlsym);
    }
    return temp;
}


int main() {
    void *libHandle;
    libHandle = dlopen("./libdeque.so", RTLD_LAZY);
    if (!libHandle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    dblinkedlist*(*createdblinkedlist)() = get(libHandle, "createdblinkedlist");
    void(*Delete_dblinkedlist)(dblinkedlist **l) = get(libHandle, "Delete_dblinkedlist");
    void(*Printdblinkedlist)(dblinkedlist *l) = get(libHandle, "Printdblinkedlist");
    void(*PushBack)(dblinkedlist *list, int value) = get(libHandle, "PushBack");
    Node*(*PopBack)(dblinkedlist *l) = get(libHandle, "PopBack");
    void(*PushFront)(dblinkedlist *l, int data) = get(libHandle, "PushFront");
    Node*(*PopFront)(dblinkedlist *l) = get(libHandle, "PopFront");
    dblinkedlist *l = (*createdblinkedlist)();
    char c;
    int a;
    help();
    while (true) {
        scanf("%c", &c);
        switch (c) {
            case 'a':
                printf("Your element\n");
                scanf("%d", &a);
                (*PushBack)(l, a);    
            break;
            case 'd':
                (*PopBack)(l);
            break;
            case 't':
                printf("Your element\n");
                scanf("%d", &a);
                (*PushFront)(l,a); 
            break;
            case 'e':
                (*Delete_dblinkedlist)(&l);
                dlclose(libHandle);
                return 0;
            break;
            case 'h':
                help();
            break;
            case 'p':
                (*Printdblinkedlist)(l);
            break;
            case 'l':
                printf("size:%lu\n",l->size);
            break;
            case 'r':
                (*PopFront)(l);
            break;
        }
    }
    return 0;
}
