#ifndef ILIST
#define ILIST

typedef struct List_element{
    void *data;
    struct List_element *next;
    struct List_element *prev;
} List_element;

typedef struct List{
    List_element *head;
    List_element *tail;
    int size;
    int (*destroy)(void *data);
    char* (*tostr)(void *data);
} List; 

List *list_create(int (*des)(void *data),char* (*to_str)(void *data));
void list_append(List *list, void *val);
void list_prepend(List *list, void *val);
void list_insert(List *list, int index, void *val);
void list_print(List *list);
void list_clear(List *list);
void list_remove(List *list, int index);
void list_element_at(List *list, int index);
void list_find_first(List *list, void *val);

#endif
