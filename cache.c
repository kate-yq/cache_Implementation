// implementation of cache.h
#include "cache.h"
#include "intmap.h"
#include "lru.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// implementation of cache_init
Cache_t *cache_init(int size, int mode) {
  Cache_t *cache = (Cache_t *)malloc(sizeof(Cache_t));
  cache->messages = (Message_t **)malloc(size * sizeof(Message_t *));
  if (cache->messages == NULL) {
    free(cache); // Free previously allocated memory
    return NULL; // Memory allocation failed
  }
  cache->size = size;
  cache->indexMap = init_intMap(size);
  cache->messageCount = 0;
  cache->cacheHit = 0;
  cache->cacheMiss = 0;
  cache->lru = lru_init(size);
  cache->mode = mode;
  cache->randomSeed = (unsigned int)time(NULL);
  srand(cache->randomSeed);
  return cache;
}

// find in cache, if not found, return null
Message_t *cfind_msg(Cache_t *cache, int id) {
  if (cache == NULL) {
    return NULL;
  }
  int index = intMap_get(cache->indexMap, id);

  // not found, cacheMiss + 1
  if (index == -1) {
    cache->cacheMiss++;
    return NULL;
  }

  // found, update lru if mode is LRU
  if (cache->mode == 1) {
    lru_find(cache->lru, id);
  }

  // printf("index: %d\n", index);
  // if (cache->messages[index] == NULL) {
  //   printf("message index is NULL\n");
  // }
  cache->cacheHit++;
  return cache->messages[index];
}

// write message into cache
// replace mode: if cache is full, replace the least recently used message
// the checking logic should be in the caller (message)
// return status code, 0 if no error, 1 if error
int cstore_msg(Cache_t *cache, Message_t *message) {
  // printf("enter cstore_msg\n");
  if (cache == NULL || message == NULL) {
    return 1;
  }

  int messageID = message->id;

  // check if the message is already in the cache
  if (intMap_get(cache->indexMap, messageID) != -1) {
    return 1;
  }

  int index = cache->messageCount;
  if (cache->mode == 0) { // random mode
    // full, need replace
    if (index == cache->size) {
      index = rand() % cache->size;
      int prev_messageID = cache->messages[index]->id;
      intMap_delete(cache->indexMap, prev_messageID);
      cache->messageCount--;
    }
  } else if (cache->mode == 1) { // LRU mode
    int idToReplace = lru_write(cache->lru, messageID);
    // printf("id to replace %d\n", idToReplace);
    // full, find the index to replace
    if (idToReplace != -1) {
      index = intMap_get(cache->indexMap, idToReplace);
      intMap_delete(cache->indexMap, idToReplace);
      cache->messageCount--;
    }
  }
  // check if the index has existing message, if yes, free it
  if (cache->messages[index] != NULL) {
    free(cache->messages[index]);
  }
  // fill the index
  // printf("index to fill %d\n", index);
  cache->messages[index] = message;
  intMap_insert(cache->indexMap, messageID, index);
  cache->messageCount++;
  // printf("exit cstore_msg\n");
  return 0;
}

void freeCache(Cache_t *cache) {
  if (cache == NULL) {
    return;
  }
  free_intMap(cache->indexMap);
  free_lru(cache->lru);
  for (int i = 0; i < cache->size; i++) {
    if (cache->messages[i] != NULL) {
      free(cache->messages[i]);
    }
  }

  free(cache->messages);
  free(cache);
}
