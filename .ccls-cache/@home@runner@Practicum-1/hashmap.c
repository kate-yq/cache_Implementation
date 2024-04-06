// implementation of hashmap.h
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

HashMap_t *init_hashMap(int size) {
  HashMap_t *map = (HashMap_t *)malloc(sizeof(HashMap_t));
  map->buckets = (HNode_t **)malloc(size * sizeof(HNode_t *));
  if (map->buckets == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  map->size = size;

  // Initialize each bucket to NULL
  for (int i = 0; i < size; ++i) {
    map->buckets[i] = NULL;
  }
  return map;
}

void hashMap_insert(HashMap_t *map, int key, void *value) {
  // Calculate the hash value for the key
  int index = key % map->size;

  // Create a new node for the hashmap entry
  HNode_t *newNode = (HNode_t *)malloc(sizeof(HNode_t));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  newNode->key = key;
  newNode->value = value;
  newNode->next = NULL;

  // Add the new node to the beginning of the linked list
  newNode->next = map->buckets[index];
  map->buckets[index] = newNode;
}

// return 0 if found, -1 if not found
int hashMap_containsKey(HashMap_t *map, int key) {
  // Calculate the hash value for the key
  int index = key % map->size;

  // Traverse the linked list at the index to find the matching key
  HNode_t *current = map->buckets[index];
  while (current != NULL) {
    if (current->key == key) {
      return 0;
    }
    current = current->next;
  }

  // Key not found
  return -1;
}

void *hashMap_get(HashMap_t *map, int key) {
  // Calculate the hash value for the key
  int index = key % map->size;

  // Traverse the linked list at the index to find the matching key
  HNode_t *current = map->buckets[index];
  while (current != NULL) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }

  // Key not found
  return NULL;
}

void hashMap_delete(HashMap_t *map, int key) {
  int index = key % map->size;
  HNode_t *prev = NULL;
  HNode_t *current = map->buckets[index];

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

void free_hashMap(HashMap_t *map) {
  // Free each linked list in the buckets
  for (int i = 0; i < map->size; ++i) {
    HNode_t *current = map->buckets[i];
    while (current != NULL) {
      HNode_t *temp = current;
      current = current->next;
      free(temp);
    }
  }

  // Free the array of buckets
  free(map->buckets);
  // Free the hashmap structure
  free(map);
}
