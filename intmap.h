// Define the hashtable data structure used in the cache, allowing fast lookups
#ifndef INTMAP_H
#define INTMAP_H

#include <stdlib.h>

// Define the structure for each node in the hashmap
typedef struct IntNode {
  int key;
  int value;
  struct IntNode *next;
} IntNode_t;

// Define the hashmap structure
typedef struct {
  IntNode_t **buckets;
  int size;
} IntMap_t;

IntMap_t *init_intMap(int size);
void intMap_insert(IntMap_t *map, int key, int value);
int intMap_get(IntMap_t *map, int key);
void intMap_delete(IntMap_t *map, int key);
void free_intMap(IntMap_t *map);

#endif /* INTMAP_H */