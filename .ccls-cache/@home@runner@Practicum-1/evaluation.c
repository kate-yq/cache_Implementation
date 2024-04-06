// Implementation of evaluation.h
#include "evaluation.h"
#include "cache.h"
#include "io.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// generate num_messages of random messages
// start indexing from offset
// store them into disk and cache
// return status code
int generate_messages(int num_messages, int offset, Cache_t *cache) {
  char *sender = "sender";
  char *receiver = "receiver";
  char *content = "Hello, world!";
  for (int i = offset; i < num_messages + offset; i++) {
    Message_t *msg = create_msg(i, sender, receiver, content);
    if (msg == NULL) {
      fprintf(stderr, "Error: Failed to create message\n");
      return 1;
    }
    if (store_msg(msg, cache) != 0) {
      fprintf(stderr, "Error: Failed to store message\n");
      return 1;
    }
  }
  return 0;
}

// retrieve num_messages of random messages from a range of id
// return status code
int access_random_msg(int num_messages, int total, Cache_t *cache) {
  srand(time(NULL));
  if (num_messages <= 0 || total <= 0) {
    fprintf(stderr, "Error: Invalid input\n");
    return 1;
  }
  for (int i = 0; i < num_messages; i++) {
    int id = (rand() % total) + 1;
    Message_t *msg = retrieve_msg(id, cache);
    if (msg == NULL) {
      fprintf(stderr, "Error: Failed to retrieve message\n");
      return 1;
    }
  }
  return 0;
}

// print the cache statistics
void show_cache_stats(Cache_t *cache) {
  fprintf(stdout, "Cache hit: %d\n", cache->cacheHit);
  fprintf(stdout, "Cache miss: %d\n", cache->cacheMiss);
  fprintf(stdout, "Cache hit ratio: %.2f\n",
          (float)cache->cacheHit / (cache->cacheHit + cache->cacheMiss));
}
