// list.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "list.h"

inline List ListInit(uint32 content_size) {
    List list;
    list.head = NULL;
    list.end = NULL;
    list.content_size = content_size;
    list.length = 0;
    return list;
}

inline List * ListNew(uint32 content_size) {
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->end = NULL;
    list->content_size = content_size;
    list->length = 0;
    return list;
}

inline List ListCopy(List list) {
    List list_new;
    ListItem *item;
    void *content, *content_new;
    if (list.head == NULL) {
        return list;
    }
    list_new = ListInit(list.content_size);
    item = list.head;
    while (item != NULL) {
        content = item->content;
        content_new = malloc(list.content_size);
        memcpy(content_new, content, list.content_size);
        AddListItem(&list_new, content_new);
        item = item->next;
    }
    return list_new;
}

inline List * ListNewCopy(List *this) {
    List *list_new;
    ListItem *item;
    void *content, *content_new;
    if (this == NULL) {
        return NULL;
    }
    if (this->head == NULL) {
        return ListNew(this->content_size);
    }
    list_new = ListNew(this->content_size);
    item = this->head;
    while (item != NULL) {
        content = item->content;
        content_new = malloc(this->content_size);
        memcpy(content_new, content, this->content_size);
        AddListItem(list_new, content_new);
        item = item->next;
    }
    return list_new;
}

inline void ListFree(List *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->head != NULL) {
        ClearListItem(this);
    }
    if (freeThis) {
        free(this);
    }
}

inline ListItem ListItemInit(void *content, ListItem *prev, ListItem *next) {
    ListItem item;
    item.content = content;
    item.prev = prev;
    item.next = next;
    return item;
}

inline ListItem * ListItemNew(void *content, ListItem *prev, ListItem *next) {
    ListItem *item = (ListItem *)malloc(sizeof(ListItem));
    item->content = content;
    item->prev = prev;
    item->next = next;
    return item;
}

inline void ListItemFree(ListItem *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->content != NULL) {
        free(this->content);
    }
    if (freeThis) {
        free(this);
    }
}

inline ListItem * FirstListItem(List *this) {
#ifndef NODEBUG
    if (this == NULL) {
        return NULL;
    }
#endif
    return this->head;
}

inline ListItem * LastListItem(List *this) {
#ifndef NODEBUG
    if (this == NULL) {
        return NULL;
    }
#endif
    return this->end;
}

inline ListItem * PrevListItem(ListItem *item) {
#ifndef NODEBUG
    if (item == NULL) {
        return NULL;
    }
#endif
    return item->prev;
}

inline ListItem * NextListItem(ListItem *item) {
#ifndef NODEBUG
    if (item == NULL) {
        return NULL;
    }
#endif
    return item->next;
}

inline void * GetListItemContent(ListItem *item) {
#ifndef NODEBUG
    if (item == NULL) {
        return NULL;
    }
#endif
    return item->content;
}

inline uint32 GetListContentSize(List *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->content_size;
}

inline uint32 GetListLength(List *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->length;
}

void * ListToArray(List *this, uint32 *content_size, uint32 *length) {
    ListItem *item;
    void *array, *ptr;
    if (this == NULL || this->head == NULL || this->content_size == 0 || this->length == 0) {
        return NULL;
    }
    array = malloc(this->content_size * this->length);
    *content_size = this->content_size;
    *length = this->length;
    item = this->head;
    ptr = array;
    while (item != NULL) {
        if (item->content == NULL) {
            memset(ptr, 0, this->content_size);
        }
        else {
            memcpy(ptr, item->content, this->content_size);
        }
        ptr = (void *)((char*)ptr + this->content_size);
        item = item->next;
    }
    return array;
}

List ArrayToList(void *array, uint32 content_size, uint32 length) {
    List list;
    void *content;
    if (array == NULL || content_size == 0 || length == 0) {
        return ListInit(0);
    }
    list = ListInit(content_size);
    for (int i = 0; i < length; i++) {
        content = malloc(content_size);
        memcpy(content, array, content_size);
        AddListItem(&list, content);
        array = (void *)((char *)array + content_size);
    }
    return list;
}

List * ArrayToListNew(void *array, uint32 content_size, uint32 length) {
    List *list;
    void *content;
    if (array == NULL || content_size == 0 || length == 0) {
        return NULL;
    }
    list = ListNew(content_size);
    for (int i = 0; i < length; i++) {
        content = malloc(content_size);
        memcpy(content, array, content_size);
        AddListItem(list, content);
        array = (void *)((char *)array + content_size);
    }
    return list;
}

void AddListItem(List *this, void *content) {
    ListItem *item;
    if (this == NULL) {
        return;
    }
    item = this->end;
    if (item != NULL) {
        item->next = ListItemNew(content, item, NULL);
        this->end = item->next;
    }
    else {
        this->head = ListItemNew(content, NULL, NULL);
        this->end = this->head;
    }
    this->length++;
}

void InsertListItem(List *this, ListItem *item_after_insert, void *content) {
    ListItem *item;
    if (this == NULL || this->head == NULL || item_after_insert == NULL) {
        return;
    }
    if (this->head == item_after_insert) {
        this->head = ListItemNew(content, NULL, item_after_insert);
        item_after_insert->prev = this->head;
    }
    else {
        item = item_after_insert->prev;
        item->next = ListItemNew(content, item, item_after_insert);
        item_after_insert->prev = item->next;
    }
    this->length++;
}

void ExchangeListItem(List *this, ListItem *item_a, ListItem *item_b) {
    void *tmp_content;
    if (this == NULL || this->head == NULL || item_a == NULL || item_b == NULL || item_a == item_b) {
        return;
    }
    tmp_content = item_a->content;
    item_a->content = item_b->content;
    item_b->content = tmp_content;
}

void ChangeListItem(List *this, ListItem *item_to_change, void *content) {
    if (this == NULL || this->head == NULL || item_to_change == NULL) {
        return;
    }
    item_to_change->content = content;
}

void DeleteListItem(List *this, ListItem *item_to_del) {
    ListItem *item, *item_next;
    if (this == NULL || this->head == NULL || item_to_del == NULL) {
        return;
    }
    item = item_to_del->prev;
    if (item == NULL) {
        this->head = item_next = item_to_del->next;
    }
    else {
        item->next = item_next = item_to_del->next; 
    }
    if (item_next != NULL) {
        item_next->prev = item;
    }
    if (item_to_del == this->end) {
        this->end = (item_next == NULL ? item : item_next);
    }
    ListItemFree(item_to_del, true);
    this->length--;
}

void ClearListItem(List *this) {
    ListItem *item, *next;
    if (this == NULL) {
        return;
    }
    item = this->head;
    while (item != NULL) {
        next = item->next;
        ListItemFree(item, true);
        item = next;
    }
    this->head = NULL;
    this->end = NULL;
    this->length = 0;
}
