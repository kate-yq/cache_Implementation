// Define a doubly linked list and its functions
#ifndef DLL_H
#define DLL_H

#include <stdlib.h>

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
  int data;
  struct node *next;
  struct node *previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
  int count;    // count keeps track of how many items are in the DLL.
  node_t *head; // head points to the first node in our DLL.
  node_t *tail; // tail points to the last node in our DLL.
} dll_t;

dll_t *create_dll();
int dll_push_front(dll_t *l, node_t *node);
int dll_push_front_item(dll_t *l, int item);
int dll_remove(dll_t *l, node_t *node);
int dll_pop_back(dll_t *l);
int dll_size(dll_t *l);
void free_dll(dll_t *l);
void print_dll(dll_t *l);
#endif
