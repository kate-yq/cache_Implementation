// Define a hashmap data structure used for LRU caching system, and its functions
#ifndef HASHMAP_H
#define HASHMAP_H

#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

// Define the structure for each node in the hashmap
typedef struct Node {
  int key;
  void *value; // value is node in dll
  struct Node *next;
} HNode_t;

// Define the hashmap structure
typedef struct {
  HNode_t **buckets;
  int size;
} HashMap_t;

HashMap_t *init_hashMap(int size);
void hashMap_insert(HashMap_t *map, int key, void *value);
void hashMap_delete(HashMap_t *map, int key);
// return 0 if found, -1 if not found
int hashMap_containsKey(HashMap_t *map, int key);
void *hashMap_get(HashMap_t *map, int key);
void free_hashMap(HashMap_t *map);

#endif
