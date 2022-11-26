#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(Process));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, Process element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(Process));
  }

  a->array[a->used++] = element;
}


int main() {
  Array a;
  int typed;
  int serial = 0;

  initArray(&a, 10);

  while(1) {
    scanf("%d", &typed);

    if(typed == 0) {
    } else {
      showProcessTable();
    }
  }


  return 0;
}