// Implementation of message.h
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// create a new message and return it
Message_t *create_msg(int id, char *sender, char *receiver, char *content) {
  Message_t *message = (Message_t *)malloc(sizeof(Message_t));
  if (message == NULL) {
    return NULL;
  }

  message->id = id;
  message->sendTime = time(NULL);
  strncpy(message->sender, sender, sizeof(message->sender) - 1);
  message->sender[sizeof(message->sender) - 1] = '\0';
  strncpy(message->receiver, receiver, sizeof(message->receiver) - 1);
  message->receiver[sizeof(message->receiver) - 1] = '\0';
  strncpy(message->content, content, sizeof(message->content) - 1);
  message->content[sizeof(message->content) - 1] = '\0';

  return message;
}

// free the message
void free_msg(Message_t *message) {
  if (message == NULL) {
    return;
  }
  free(message);
}