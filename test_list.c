#include "IList.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#define N 1000 /* max num of char in one Course */

typedef struct course_{
  char *dept;
  char *num;
  char *instructor;
} Course;

char *course_tostr(void *data);
int course_destroy(void *data);
Course* new_course(char *dept, char *num, char *instructor);

int main(){
  List *list;
  Course *p;

  list = list_create(course_destroy,course_tostr);
  list_remove(list,5);
  list_insert(list,10,new_course("MPCS", "55001", "Brady"));
  list_append(list, new_course("MPCS", "51100", "Siegel"));
  list_prepend(list, new_course("PPHA", "30800", "Fouiranaies"));
  list_append(list, new_course("MPCS", "51100", "Siegel"));
  list_insert(list,4,new_course("PPHA", "31002", "Moskowitz"));
  list_insert(list,1,new_course("MPCS", "55002", "Brady"));
  list_remove(list,15);
  assert(list->size == 6);
  assert( strcmp( ((Course *)(list->head->data))->num, "30800") == 0);
  assert( strcmp( ((Course *)(list->tail->data))->num, "31002") == 0);
  list_element_at(list,6);
  list_element_at(list,0);
  list_element_at(list,5);

  p = new_course("MPCS", "51100", "Siegel");
  list_find_first(list, p);
  free(p);
  list_clear(list);
  list_print(list);
  printf("All tests passed.\n");
  free(list);
  return 0;

  /* Expected stdout - 
  Index value past end of list: no element was removed.
  Index value 10 past end of list: appending.
  Index value 4 past end of list: appending.
  Index value past end of list: no element was removed.
  Error - index is out of range.
  The element at index 0 is: PPHA: 30800 - Fouiranaies.
  The element at index 5 is: PPHA: 31002 - Moskowitz.
  The element MPCS: 51100 - Siegel is at index 3.
  []
  All tests passed.
  */

  /*
  List elements:
  "PPHA", "30800", "Fouiranaies"
  "MPCS", "55001", "Brady"
  "MPCS", "55002", "Brady"
  "MPCS", "51100", "Siegel"
  "MPCS", "51100", "Siegel"
  "PPHA", "31002", "Moskowitz"
  */

}

char *course_tostr(void *data){
  Course *p;
  char *arr;
  arr = (char*) malloc(N*sizeof(char)); /* list.h will free(arr) */
  p = (Course *)data;
  sprintf(arr,"%s: %s - %s",p->dept,p->num,p->instructor);
  return(arr);
}

int course_destroy(void *data){
  Course *c = (Course *)data;
  free(c);
  return 0;
}

Course* new_course(char* dept, char* num, char* instructor){
  Course *p;
  p = (Course *) malloc(sizeof(Course)); /* list_destory() will free courses */
  p->dept = dept;
  p->num = num;
  p->instructor = instructor;
  return p;
}
