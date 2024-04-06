// helper functions for evaluating the caching system and I/O process
#ifndef EVALUATION_H
#define EVALUATION_H

#include "io.h"
#include "cache.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/***
  * Generate a number of messages, store them into disk and cache
  * return status code
  */
int generate_messages(int num_messages, int offset, Cache_t *cache);

/***
  * Retrieve certain number of random messages from a range of id
  * return status code
  */
int access_random_msg(int num_messages, int total, Cache_t *cache);

/***
  * Show the cache statistics
  */
void show_cache_stats(Cache_t *cache);

#endif