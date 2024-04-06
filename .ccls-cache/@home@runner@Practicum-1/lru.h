/***
 * Define the LRU data structure and mechanisms
 * message id <-> index
 */
#ifndef LRU_H
#define LRU_H

#include "dll.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define the lru data structure fields
typedef struct {
  HashMap_t *map;
  dll_t *dll;
  int maxSize;
  int actualSize;
} Lru_t;

Lru_t *lru_init(int size);
// return find resulte, 0 if found, -1 if not found
// and update the most recently used message
int lru_find(Lru_t *lru, int id);
// return the msg_id to write message into cache
// if not full, return -1
int lru_write(Lru_t *lru, int id);
void free_lru(Lru_t *lru);

#endif