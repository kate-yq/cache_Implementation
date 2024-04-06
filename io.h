/***
 * Define the I/O operations for messages
 * Write and read messages from disk and cache
 */
#ifndef IO_H
#define IO_H

#include "cache.h"
#include "message.h"

/***
  * store into a file per message, and update cache
  * return the message id
  */
int store_msg(Message_t *message, Cache_t *cache);

/***
  * retrieve from file using id, and update cache
  * return the retrieve message, or NULL if not found
  */
Message_t *retrieve_msg(int id, Cache_t *cache);

#endif