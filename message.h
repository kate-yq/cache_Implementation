/***
 * Define the message data structure
 * Create the message with given information
 */
#ifndef MESSAGE_H
#define MESSAGE_H

#include <time.h>

// fixed-sized message defined as 512 bytes
#define MESSAGE_SIZE 512

/***
 * Define the message data structure
 * id: unique identifier generated using index
 * sendTime: system time when the message was sent
 * sender: sender's username
 * receiver: receiver's username
 * content: message content
 * delivered: flag indicating if the message has been delivered,
 *           initialed to 0
 */
typedef struct Message {
  int id;
  time_t sendTime;
  char sender[100];
  char receiver[100];
  char content[292];
  int delivered;
} Message_t;

/***
  * create a message, and return the message
  *
  * @param id: message id
  * @param sender: sender's username
  * @param receiver: receiver's username
  * @param content: message content
  *
  * @return: the message
  */ 
Message_t *create_msg(int id, char *sender, char *receiver, char *content);

/***
 * free the specific message
 *
 * @param msg: the message
 */
void free_msg(Message_t *message);

#endif