#include<stdio.h>
#include "IList.h"
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define N 1000 /* max len of char in one Point when converted to str */

struct Point_{
  char *color;
  float x;
  float y;
  float z;
};

typedef struct Point_ Point;
float dist(Point *a);
Point *create_ran_point();
void create_ran_point_arr(Point **p);
void write_file(List *list, int n);
void write_file_arr(Point **p, int n);
char *point_tostr(void *data);
int point_destroy(void *data);
void point_sort(List *list);
void work_arr(Point **p, int n, int num_iterations);
void work_list(List *list, int n, int num_iterations);

int main(int argc, char **argv){
  int i,n, num_invocations;
  List *list;
  Point **p;
  clock_t start, stop;

  n = atoi(argv[1]); 
  list = list_create(point_destroy,point_tostr);
  p = (Point **) malloc(2*n*sizeof(Point*));
  
  srand(time(NULL));
  for (i = 0; i < n; i++){
      list_append(list, create_ran_point());
      create_ran_point_arr(&p[i]);
  }

  list_print(list);

  write_file(list,n);
  write_file_arr(p,n);

  /* performance comparison between array and doubly linked list */
  num_invocations = 3000; /* number of times to invocate work function */
  start = clock();	
  work_arr(p,n,num_invocations);
  stop = clock();
  printf("Time taken to iterate through array %d times: \t%.5f (s)\n", num_invocations, (double)(stop-start)/CLOCKS_PER_SEC);
  
  start = clock();	
  work_list(list,n, num_invocations);
  stop = clock();
  printf("Time taken to iterate through list %d times: \t%.5f (s)\n", num_invocations, (double)(stop-start)/CLOCKS_PER_SEC);

  list_clear(list);
  for(i=0;i<n;++i)
    free(p[i]);
  free(p);
  free(list);
  return 0;
}  

float dist (Point *a){
  return sqrt( (a->x)*(a->x)+(a->y)*(a->y)+(a->z)*(a->z));
}

Point *create_ran_point(){
  float x,y,z;
  float a;
  Point *p;
  a = 10.0;

  p = (Point *) malloc(sizeof(Point));
  x = ((float)rand()/(float)(RAND_MAX)) * a - a/2.0;
  y = ((float)rand()/(float)(RAND_MAX)) * a - a/2.0;
  z = ((float)rand()/(float)(RAND_MAX)) * a - a/2.0;
  p->color = "Blue";
  p->x = x; p->y = y; p->z = z;
  return p;
}

void create_ran_point_arr(Point **p){
  float x,y,z;
  float a = 10.0;

  *p = (Point *) malloc(sizeof(Point));
  x = ((float)rand()/(float)(RAND_MAX)) * a - a/2.0;
  y = ((float)rand()/(float)(RAND_MAX)) * a - a/2.0;
  z = ((float)rand()/(float)(RAND_MAX)) * a - a/2.0;

  (*p)->color = "Blue"; (*p)->x = x; (*p)->y = y; (*p)->z = z;
}

void write_file(List *list, int n){
  List_element *el;
  FILE *file;
  char *the_str;
  el = list->head;
  file = fopen("data.txt", "w");
  the_str = NULL;
  while (el != NULL){
    the_str = point_tostr(el->data);
    fprintf(file, "%s\n", the_str);
    free(the_str);
    el = el->next;
  }
  fclose(file);
}

void write_file_arr(Point **p, int n){
  int i;
  FILE *file;
  file = fopen("data_arr.txt", "w");
  for (i=0;i<n;++i)
    fprintf(file, "%s %f %f %f\n", p[i]->color, p[i]->x, p[i]->y, p[i]->z);
  fclose(file);
}

char *point_tostr(void *data){
  char *arr;
  Point *p;
  p = (Point *)data;
  arr = (char*) malloc(N*sizeof(char)); /* list.h will free(arr) */
  sprintf(arr,"Color: %s; x: %6.2f; y: %6.2f; z: %6.2f",p->color,p->x,p->y,p->z);
  return(arr);
}

int point_destroy(void *data){
    Point *p = (Point *)data;
    free(p);
    return 0;
}

void work_arr(Point **p, int n, int num_iterations){
  int i,j;
  float *arr;
  arr = malloc(n*sizeof(float));
  for (j = 0; j < num_iterations; j++){
    for (i = 0; i < n; i++){
      arr[i] = dist(p[i]);
    }
  }
  free(arr);
}

void work_list(List *list, int n, int num_iterations){
  int i,j;
  float *arr;
  List_element *el;
  arr = malloc(n*sizeof(float));
  for (j = 0; j < num_iterations; j++){
    for (i = 0, el = list->head; el != NULL; el = el->next, i++){
      arr[i] = dist((Point*) el->data);
    }
  }
  free(arr);
}
