// implemenation of dll.h
#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t *create_dll() {
  // Modify the body of this function as needed.
  dll_t *my_dll = (dll_t *)malloc(sizeof(dll_t));

  if (my_dll == NULL) {
    return NULL;
  }

  my_dll->head = NULL;
  my_dll->tail = NULL;
  my_dll->count = 0;

  return my_dll;
}

// print DLL
void print_dll(dll_t *l) {
  if (l == NULL || l->head == NULL) {
    printf("DLL is empty or NULL.\n");
    return;
  }

  printf("DLL contains %d items: ", l->count);

  node_t *current = l->head;

  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }

  printf("\n");
}

// push a node to the front of the DLL (before the first node in the list).
// Returns 0 on success
// Returns -1 if DLL is NULL.
int dll_push_front(dll_t *l, node_t *node) {
  if (l == NULL) {
    printf("Error: DLL is NULL\n");
    return -1;
  }

  node->next = l->head;
  if (l->head != NULL) {
    l->head->previous = node;
  }
  l->head = node;
  if (l->tail == NULL) {
    l->tail = node;
  }

  l->count++;

  return 0;
}

// push a new item to the front of the DLL (before the first node in the list).
// Returns 0 on success
// Returns -1 if DLL is NULL.
int dll_push_front_item(dll_t *l, int item) {
  if (l == NULL) {
    return -1;
  }

  node_t *new_node = (node_t *)malloc(sizeof(node_t));

  if (new_node == NULL) {
    return -1;
  }

  new_node->data = item;
  new_node->previous = NULL;

  if (l->head == NULL) {
    l->head = new_node;
    l->tail = new_node;
    new_node->next = NULL;
  } else {
    l->head->previous = new_node;
    new_node->next = l->head;
    l->head = new_node;
  }

  l->count++;

  return 0;
}

// remove the node from dll
// Returns 0 on success
// Returns -1 if DLL is NULL.
int dll_remove(dll_t *l, node_t *node) {
  if (l == NULL) {
    return -1;
  }

  node_t *node_prev = node->previous;
  node_t *node_next = node->next;

  if (node_prev != NULL) {
    node_prev->next = node_next;
  } else {
    l->head = node_next;
  }

  if (node_next != NULL) {
    node_next->previous = node_prev;
  } else {
    l->tail = node_prev;
  }

  node->previous = NULL;
  node->next = NULL;
  l->count--;
  return 0;
}

// Return status code, 0 if no error, 1 if error
int dll_pop_back(dll_t *l) {

  if (l == NULL) {
    return -1;
  }

  if (l->count == 0) {
    return -1;
  }

  node_t *node_popped = l->tail;

  if (l->count == 1) {
    l->head = NULL;
    l->tail = NULL;
  } else {
    l->tail = l->tail->previous;
    // for test purpose, print dll
    // print_dll(l);
    l->tail->next = NULL;
  }

  l->count--;

  free(node_popped);

  return 0;
}

// DLL Size
// Queries the current size of a DLL
// Returns -1 if the DLL is NULL.
int dll_size(dll_t *l) {
  if (l == NULL) {
    return -1;
  }

  return l->count;
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the program terminates.
void free_dll(dll_t *l) {
  if (l == NULL) {
    exit(1);
  }

  node_t *iterator = l->head;

  while (iterator != NULL) {
    node_t *temp = iterator;
    iterator = iterator->next;
    free(temp);
  }

  free(l);
}
