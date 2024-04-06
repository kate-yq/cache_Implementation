// implementation of lru.h
#include "lru.h"
#include "dll.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// implementation of lru_init
Lru_t *lru_init(int size) {
  Lru_t *lru = (Lru_t *)malloc(sizeof(Lru_t));
  lru->maxSize = size;
  lru->actualSize = 0;
  lru->map = init_hashMap(size);
  lru->dll = create_dll();
  return lru;
}

// return find resulte, 0 if found, -1 if not found
// and update the most recently used message
int lru_find(Lru_t *lru, int id) {
  // printf("enter lru find\n");
  if (lru == NULL || lru->map == NULL) {
    printf("Error: Invalid input\n");
    return -1;
  }
  if (hashMap_containsKey(lru->map, id) == -1) {
    // not found
    printf("Not found\n");
    return -1;
  }

  node_t *node = hashMap_get(lru->map, id);

  // remove node form dll
  dll_remove(lru->dll, node);

  // add node to front of dll
  dll_push_front(lru->dll, node);
  // free(node);

  // hashMap_delete(lru->map, id);
  // hashMap_insert(lru->map, id, lru->dll->head);
  // printf("exit lru find\n");
  return 0;
}

// return the msg_id to write message into cache
// if not full, return -1
int lru_write(Lru_t *lru, int id) {
  // printf("enter lru write\n");
  if (lru == NULL || lru->map == NULL) {
    printf("Error: Invalid input\n");
    return -1;
  }

  int idToDrop = -1;

  // if full, kick the last one, update idTodrop
  if (lru->actualSize >= lru->maxSize) {
    idToDrop = lru->dll->tail->data;
    if (dll_pop_back(lru->dll) != 0) {
      printf("error pop back in LRU-dll\n");
      return -1;
    }
    // printf("bp\n");

    hashMap_delete(lru->map, idToDrop);
    lru->actualSize--;
  }

  // add value to front of dll
  dll_push_front_item(lru->dll, id);

  // add node to hashmap
  hashMap_insert(lru->map, id, lru->dll->head);

  lru->actualSize++;

  // printf("exit lru write\n");
  return idToDrop;
}

void free_lru(Lru_t *lru) {
  free_dll(lru->dll);
  free_hashMap(lru->map);
  free(lru);
}