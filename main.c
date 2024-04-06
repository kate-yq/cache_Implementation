/***
 * main.c / DO: Practicum I
 *
 * Yidan Cong, Quan Yuan / CS5600 / Northeastern University
 * Spring 2024 / Mar 27, 2024
 *
 * To run the program from the shell:
 * 1. make
 * 2. ./practicum
 * (The program executable is named 'practicum')
 *
 * Please read README.md for more information.
 */

// main process of the program
#include "cache.h"
#include "evaluation.h"
#include "io.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CACHE_SIZE 300
#define NUM_MESSAGES 100
// mode: 0 - random, 1 - LRU
// #define CACHE_REPLACEMENT_MODE 0
#define CACHE_REPLACEMENT_MODE 1

int main(void) {
  // initialize cache
  Cache_t *cache = cache_init(CACHE_SIZE, CACHE_REPLACEMENT_MODE);
  if (cache == NULL) {
    fprintf(stderr, "Error: Failed to initialize cache\n");
    return 1;
  }

  // initiate global message index
  int index = 0;

  for (int round = 0; round < 10; round++) {
    // generate and store a batch of messages
    if (generate_messages(NUM_MESSAGES, index + 1, cache) != 0) {
      fprintf(stderr, "Error: Failed to generate messages\n");
      return 1;
    }

    index = index + NUM_MESSAGES;

    // access random messages
    if (access_random_msg(NUM_MESSAGES, index, cache) != 0) {
      fprintf(stderr, "Error: Failed to access random messages\n");
      return 1;
    }
  }
  // show cache statistics
  show_cache_stats(cache);

  // free cache
  freeCache(cache);

  return 0;
}
