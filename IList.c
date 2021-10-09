#include "IList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List *list_create(int (*des)(void *data),char* (*to_str)(void *data)){
    List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destroy = des;
    list->tostr = to_str;
    return (list);
}

void list_append(List *list, void *val){
    List_element *curr, *prev;
    prev = list->tail;
    curr = malloc(sizeof(List_element)); 
    curr->data = val;
    curr->next = NULL;
    list->tail = curr;

    if (list->head == NULL){
      list->head = curr;
      curr->prev = NULL;
    }
    else{
      curr->prev = prev;
      prev->next = curr;
    }

    ++list->size;
}

void list_prepend(List *list, void *val){
  List_element *curr, *next;
  next = list->head;
  curr = malloc(sizeof(List_element));
  curr->data = val;
  list->head = curr;
  curr->prev = NULL;
  curr->next = next;

  if (next == NULL) 
    list->tail = curr;
  else
    next->prev = curr;

  ++list->size;
}

void list_insert(List *list, int index, void *val){
  List_element *el, *prev, *new;
  int count;
  prev = NULL;

  if (list->size < index + 1){
    printf("Index value %d past end of list: appending.\n", index);
    list_append(list,val);
    return;
  }
    
  for (count = 0, el = list->head; el != NULL; el = el->next, ++count){
    if (count == index){
      prev = el;
      break;
    }
  }
  
  new = malloc(sizeof(List_element));
  new->data = val;
  new->prev = prev;
  new->next = prev->next;
  prev->next = new;
  ++list->size; 
}

void list_print(List *list){
  List_element *el;
  char *str_el;
  printf("[");
  for (el = list->head; el != NULL; el = el->next){
    str_el = list->tostr(el->data);
    printf("%s", str_el);
    free(str_el);
    if (el->next != NULL)
      printf(", ");
  }
  printf("]\n");
}

void list_clear(List *list){
  List_element *el;
  el = list->head;
  while (el != NULL){
    List_element *next;
    next = el->next;
    list->destroy(el->data);
    free(el);
    el = next;
  }
  list->head = NULL;
  list->tail = list->head;
  list->size = 0;
}

void list_remove(List *list, int index){
  List_element *el;
  int count;
  if (list->size == 0 || index >= list->size){
    printf("Index value past end of list: no element was removed.\n");
    return;
  }
  for (count = 0, el = list->head; el != NULL; count++, el = el->next){
    if (count == index)
      break;
  }
  if (el->prev != NULL)
    el->prev->next = el->next;
  else
    list->head = el->next;
  if (el->next != NULL)
    el->next->prev = el->prev;
  else
    list->tail = el->prev;
  list->destroy(el->data);
  free(el);
  (list->size)--;
}

void list_element_at(List *list, int index){
  List_element *el;
  int count;
  if (index >= (list->size)){ 
    printf("Error - index is out of range.\n");
    return;
  }
  for (count = 0, el = list->head; el != NULL; el = el->next, ++count){
    if (count == index){
      char *str;
      str = list->tostr(el->data);
      printf("The element at index %d is: %s.\n", index, str); 
      free(str);
      return;
    }
  }
}

void list_find_first(List *list, void *val){
  int index;
  List_element *el;
  char *str_list, *str_val;
  if (list->size == 0){
    printf("%s", "Error - list is empty.");
    return;
  } 
  str_val = list->tostr(val);
  str_list = NULL;
  for (index=0, el = list->head; el != NULL; el = el->next, ++index){
    str_list = list->tostr(el->data);
    if (strcmp(str_val,str_list) == 0){
      printf("The element %s is at index %d.\n", str_val, index);
      free(str_val);
      free(str_list);
      return;
    }
    else
      free(str_list);
  }
  printf("%s", "Error - element was not found in list.");
  if (str_val != NULL)
    free(str_val);
  if (str_list != NULL)
    free(str_list);
  return;
}
