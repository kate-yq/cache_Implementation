/***
 * Define the cache data structure and mechanisms
 */
#ifndef CACHE_H
#define CACHE_H

#include "hashmap.h"
#include "intmap.h"
#include "lru.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Message;

// define the cache data structure
typedef struct Cache {
  // array size input by user
  Message_t **messages;
  int size;
  IntMap_t *indexMap;
  int messageCount;
  int cacheHit;
  int cacheMiss;
  Lru_t *lru;
  int mode;
  unsigned int randomSeed; // Random seed
} Cache_t;

/***
 * Create a cache, and return the cache
 * mode: 0 - random, 1 - LRU
 */
Cache_t *cache_init(int size, int mode);

/***
 * find in cache, if not found, return null
 */
Message_t *cfind_msg(Cache_t *cache, int id);

// write message into cache
// replace mode: if cache is full, replace the least recently used message
// return status code, 0 if no error, 1 if error
int cstore_msg(Cache_t *cache, Message_t *message);

/***
 * Free the cache
 */
void freeCache(Cache_t *cache);

#endif