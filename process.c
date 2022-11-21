#include <stdio.h>
#include <stdlib.h>

// struct process {
//   int id;
//   char name;
// };

typedef struct {
  int id;
  char name;
} Process;

typedef struct {
  Process *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, Process element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }

  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

int main() {
  Process s1;
  Array a;
  s1.name = 'x';
  s1.id = 1;

  initArray(&a, 10);

  insertArray(&a, s1);

  printf("%ld\n", a.used); 

  freeArray(&a);

  printf("%ld\n", a.used); 

  return 0;
}