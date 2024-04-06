// implementation of intmap.h
#include "intmap.h"
#include <stdio.h>

// Function to initialize the hashmap
IntMap_t *init_intMap(int size) {
  IntMap_t *map = (IntMap_t *)malloc(sizeof(IntMap_t));
  if (map == NULL) {
    return NULL; // Memory allocation failed
  }

  map->buckets = (IntNode_t **)calloc(size, sizeof(IntNode_t *));
  if (map->buckets == NULL) {
    free(map);
    return NULL; // Memory allocation failed
  }
  map->size = size;
  return map;
}

// Function to insert a key-value pair into the hashmap
void intMap_insert(IntMap_t *map, int key, int value) {
  int index = key % map->size;

  IntNode_t *newNode = (IntNode_t *)malloc(sizeof(IntNode_t));
  if (newNode == NULL) {
    // Handle memory allocation failure
    return;
  }
  newNode->key = key;
  newNode->value = value;
  newNode->next = map->buckets[index];
  map->buckets[index] = newNode;
}

// Function to retrieve the value associated with a given key from the hashmap
int intMap_get(IntMap_t *map, int key) {
  int index = key % map->size;
  IntNode_t *current = map->buckets[index];
  while (current != NULL) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }
  return -1; // Key not found
}

void intMap_delete(IntMap_t *map, int key) {
  int index = key % map->size;
  IntNode_t *prev = NULL;
  IntNode_t *current = map->buckets[index];

  // Find the node with the given key
  while (current != NULL) {
    if (current->key == key) {
      // Node found, delete it
      if (prev == NULL) {
        // If the node to delete is the first node in the bucket
        map->buckets[index] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
}

// Function to free the hashmap and its nodes
void free_intMap(IntMap_t *map) {
  for (int i = 0; i < map->size; ++i) {
    IntNode_t *current = map->buckets[i];
    while (current != NULL) {
      IntNode_t *temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(map->buckets);
  free(map);
}