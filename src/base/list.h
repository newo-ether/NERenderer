// list.h

#ifndef _LIST_H_ // _LIST_H_
#define _LIST_H_

#include <stdbool.h>

// Iterators for List
#define ListForeachItem(_list, _item) for (_item = FirstListItem(_list); _item != NULL; _item = NextListItem(_item))

#define ListInvForeachItem(_list, _item) for (_item = LastListItem(_list); _item != NULL; _item = PrevListItem(_item))

#define ListForeachContent(_list, _content, _content_type) \
    _content = (_content_type *) GetListItemContent(FirstListItem(_list)); \
    for (ListItem *_item = FirstListItem(_list); _item != NULL; _item = NextListItem(_item), _content = (_content_type *) GetListItemContent(_item))

#define ListInvForeachContent(_list, _content, _content_type) \
    _content = (_content_type *) GetListItemContent(LastListItem(_list)); \
    for (ListItem *_item = LastListItem(_list); _item != NULL; _item = PrevListItem(_item), _content = (_content_type *) GetListItemContent(_item))

#ifndef _UINT32_ // _UINT32_
#define _UINT32_

typedef unsigned int uint32;

#endif // _UINT32_

typedef struct ListItem {
    void *content;
    struct ListItem *prev;
    struct ListItem *next;
} ListItem;


typedef struct List {
    struct ListItem *head;
    struct ListItem *end;
    uint32 content_size;
    uint32 length;
} List;


// List Constructor
inline List ListInit(uint32 content_size);

// List New Constructor
inline List * ListNew(uint32 content_size);

// List Copy Constructor
inline List ListCopy(List list);

// List New Copy Constructor
inline List * ListNewCopy(List *this);

// List Deconstructor
inline void ListFree(List *this, bool freeThis);


// ListItem Constructor
inline ListItem ListItemInit(void *content, ListItem *prev, ListItem *next);

// ListItem New Constructor
inline ListItem * ListItemNew(void *content, ListItem *prev, ListItem *next);

// ListItem Deconstructor
inline void ListItemFree(ListItem *this, bool freeThis);


inline ListItem * FirstListItem(List *this);

inline ListItem * LastListItem(List *this);

inline ListItem * PrevListItem(ListItem *item);

inline ListItem * NextListItem(ListItem *item);


inline void * GetListItemContent(ListItem *item);

inline uint32 GetListContentSize(List *this);

inline uint32 GetListLength(List *this);


void * ListToArray(List *this, uint32 *content_size, uint32 *length);

List ArrayToList(void *array, uint32 content_size, uint32 length);

List * ArrayToListNew(void *array, uint32 content_size, uint32 length);


void AddListItem(List *this, void *content);

void InsertListItem(List *this, ListItem *item_after_insert, void *content);

void ExchangeListItem(List *this, ListItem *item_a, ListItem *item_b);

void ChangeListItem(List *this, ListItem *item_to_change, void *content);

void DeleteListItem(List *this, ListItem *item_to_del);

void ClearListItem(List *this);

#endif // _LIST_H_
