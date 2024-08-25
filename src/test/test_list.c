// test_list.c

#include <stdio.h>
#include <stddef.h>
#include <malloc.h>
#include "../base/list.h"

void printAll(List *list) {
    char *ptr;
    ListForeachContent(list, ptr, char) {
        printf("%c ", *ptr);
    }
    printf("\n");
}

void printAllInv(List *list) {
    char *ptr;
    ListInvForeachContent(list, ptr, char) {
        printf("%c ", *ptr);
    }
    printf("\n");
}

int main() {
    List list, list_new;
    char *c;
    void *array, *ptr;
    uint32 content_size, length;
    list = ListInit(1);
    for (int i = 0; i < 26; i++) {
        c = (char *)malloc(sizeof(char));
        *c = 'a' + i;
        AddListItem(&list, c);
    }
    printf("%d\n", GetListLength(&list));
    printAll(&list);
    printAllInv(&list);
    
    DeleteListItem(&list, FirstListItem(&list));
    printf("%d\n", GetListLength(&list));
    printAll(&list);
    printAllInv(&list);
    
    DeleteListItem(&list, NextListItem(NextListItem(FirstListItem(&list))));
    printf("%d\n", GetListLength(&list));
    printAll(&list);
    printAllInv(&list);

    DeleteListItem(&list, LastListItem(&list));
    printf("%d\n", GetListLength(&list));
    printAll(&list);
    printAllInv(&list);

    c = (char *)malloc(sizeof(char));
    *c = '1';
    InsertListItem(&list, FirstListItem(&list), c);
    printf("%d\n", GetListLength(&list));
    printAll(&list);
    printAllInv(&list);

    c = (char *)malloc(sizeof(char));
    *c = '2';
    InsertListItem(&list, LastListItem(&list), c);
    printf("%d\n", GetListLength(&list));
    printAll(&list);
    printAllInv(&list);

    array = ListToArray(&list, &content_size, &length);
    ptr = array;
    for (int i = 0; i < length; i++) {
        printf("%c ", *(char *)ptr);
        ptr = (void *)((char *)ptr + 1);
    }
    printf("\n");
    free(array);

    c = (char *)malloc(sizeof(char));
    *c = 'f';
    printf("ready to free list.\n");
    ListFree(&list, false);
    printf("successfully freed.\n");
    list = ListInit(1);
    printf("%d\n", GetListLength(&list));
    AddListItem(&list, c);
    printf("%d\n", GetListLength(&list));
    printAll(&list);
    printAllInv(&list);
    DeleteListItem(&list, LastListItem(&list));
    printf("%d\n", GetListLength(&list));
    printAll(&list);
    printAllInv(&list);
    ListFree(&list, false);

    array = (char *)malloc(sizeof(char) * 26);
    ptr = array;
    for (int i = 0; i < 26; i++) {
        *(char *)ptr = 'a' + i;
        ptr = (void *)((char *)ptr + 1);
    }
    list = ArrayToList(array, 1, 26);
    printAll(&list);
    printAllInv(&list);
    free(array);

    list_new = ListCopy(list);
    printAll(&list_new);
    printAllInv(&list_new);

    ListFree(&list, false);
    ListFree(&list_new, false);

    return 0;
}
