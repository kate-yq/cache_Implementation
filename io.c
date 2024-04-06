// Implementation of io.h
#include "io.h"
#include "cache.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the root directory on disk
// Store each message as an individual binary file
#define ROOT_DIRECTORY "disk"

// store the message to a file on the disk, and add it to cache
// return status code 0 if no error, 1 if error
int store_msg(Message_t *message, Cache_t *cache) {
  if (message == NULL) {
    fprintf(stderr, "Error: Message is NULL\n");
    return 1;
  }

  char filename[41];
  snprintf(filename, sizeof(filename), "%s/%d.bin", ROOT_DIRECTORY,
           message->id);

  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  size_t written = fwrite(message, sizeof(Message_t), 1, file);
  if (written != 1) {
    fprintf(stderr, "Failed to write message to file\n");
  }
  fclose(file);

  // add the message to the cache
  cstore_msg(cache, message);

  return 0;
}

// retrieve the message from the cache,
// if not found in cache, then generate a new message from disk file
// then add the message to cache
Message_t *retrieve_msg(int id, Cache_t *cache) {
  if (id < 0 || cache == NULL) {
    fprintf(stderr, "Error: Message id is NULL\n");
    return NULL;
  }

  // first look up in cache
  Message_t *msg = cfind_msg(cache, id);
  if (msg != NULL) {
    return msg;
  }

  // if not found in cache, look up in file
  char filename[41];
  snprintf(filename, sizeof(filename), "%s/%d.bin", ROOT_DIRECTORY, id);
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    perror("Error opening file");
    return NULL;
  }

  msg = (Message_t *)malloc(sizeof(Message_t));
  if (msg == NULL) {
    fprintf(stderr, "Error: Failed to allocate memory\n");
    fclose(file);
    return NULL;
  }

  if (fread(msg, sizeof(Message_t), 1, file) != 1) {
    fprintf(stderr, "Error: Failed to read message from file\n");
    fclose(file);
    free(msg);
    return NULL;
  }

  fclose(file);

  // update this message into cache
  cstore_msg(cache, msg);

  return msg;
}